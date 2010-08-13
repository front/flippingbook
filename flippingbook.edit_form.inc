<?php

function flippingbook_book_settings_defaults() {
  $settings['bookWidth'] = 1000;
  $settings['bookHeight'] = 667;
  $settings['pageBackgroundColor'] = '#c2c2c2'; // baksiden av boka
  $settings['backgroundColor'] = '#b3b3b3';
  $settings['zoomUIColor'] = '#919d6c';
//  $settings['useCustomCursors'] = false;
  $settings['dropShadowEnabled'] = false;
  $settings['zoomImageWidth'] = 1061;
  $settings['zoomImageHeight'] = 1472;
  $settings['flipSound'] = "sounds/02.mp3";
  $settings['flipCornerStyle'] = "first page only";
  $settings['zoomHintEnabled'] = false;
  $settings['jsInitCode'] = '';
  $settings['zoomImagecachePreset'] = '';
  
  return $settings;
}


function flippingbook_book_settings_form($settings = null) {
  $defaults = flippingbook_book_settings_defaults();
  if (!is_array($settings) || count($settings) == 0) {
    $settings = variable_get('flippingbook_book_settings', array()); 
  }
  
  $settings += $defaults;
  
  $titles['bookWidth'] = t('Book Width');
  $titles['bookHeight'] = t('Book Height');
  $titles['pageBackgroundColor'] = t('Page Background Color');
  $titles['backgroundColor'] = t('Background Color');
  $titles['zoomUIColor'] = t('Zoom UI Color');
//  $titles['useCustomCursors'] = t('Use Custom Cursors');
  $titles['dropShadowEnabled'] = t('Drop Shodow Enabled');
  $titles['zoomImageWidth'] = t('Zoom Image Width');
  $titles['zoomImageHeight'] = t('Zoom Image Height');
  $titles['flipSound'] = t('Flip Sound');
  $titles['flipCornerStyle'] = t('Flip Corner Style');
  $titles['zoomHintEnabled'] = t('Zoom Hint Enabled');
  $titles['jsInitCode'] = t('Advanced Settings');
    
  $options['flipCornerStyle'] = array(
    "first page only" => t("automatically flip corner for the first page only"), 
    "each page" => t("automatically flip corner for all pages"), 
    "manually" => t("don't flip corner automatically"), 
  );
  
  $descriptions['jsInitCode'] = t('Put javascript code for advanced FlippingBook initialization here');
  
  if (module_exists('imagecache')) {
    $titles['zoomImagecachePreset'] = t('Zoom ImageCache Preset');
    $presets = array('' => t('<none>'));
    foreach (module_invoke('imagecache', 'presets') as $preset) {
      $presets[$preset['presetname']] = $preset['presetname'];
    }
    $options['zoomImagecachePreset'] = $presets;
  }

  foreach ($settings as $key => $value) {
    $form[$key] = array(
      '#type' => 'textfield',
      '#title' => $titles[$key],
      '#description' => @$descriptions[$key],
      '#default_value' => $value,
    );
    
    if (stripos($key, 'enabled') > -1) {
      $form[$key]['#type'] = 'checkbox';
    }
    elseif (stripos($key, 'color') > -1 && module_exists('colorpicker')) {
      $form[$key]['#type'] = 'colorpicker_textfield';
    }
    elseif (isset($options[$key])) {
      $form[$key]['#type'] = 'select';
      $form[$key]['#options'] = $options[$key];
    }
  }
  
  return $form;
}

function flippingbook_edit_form(&$form_state, $node) {
  $form['#node'] = $node;
  
  if (!isset($form_state['values']['contents'])) {
    if (is_array($node->flippingbook['contents'])) {
      $contents = array();
      
      foreach ($node->flippingbook['contents'] as $index => $item) {
         $item[] = $index;
         $contents[] = array_combine(array('title', 'page', 'weight'), $item);
      }
      
      $form_state['values']['contents'] = $contents;
    }
  }

  $form['contents_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Table of contents'),
  );
  $form['contents_container'] += flippingbook_contents_form($form_state);
  
  $form['settings'] = array(
    '#tree' => true,
    '#type' => 'fieldset',
    '#title' => t('Custom Settings'),
    '#collapsible' => true,
    '#collapsed' => true,
  );
  
  $form['settings'] += flippingbook_book_settings_form($node->flippingbook['settings']);
  $form['settings']['jsInitCode']['#access'] = user_access('edit flippingbook advanced settings');
  $form['settings']['jsInitCode']['#type'] = 'textarea';
  
  $form['submit'] = array(
    '#type' => 'submit',  
    '#value' => 'Save',
  );
                       
  return $form;
}

function flippingbook_edit_form_submit($form, &$form_state) {
  $flippingbook = array(
    'nid' => $form['#node']->nid,
    'settings' => $form_state['values']['settings'],
  );

  $contents = array();
  foreach($form_state['values']['contents'] as $item) {
    $contents[] = array(filter_xss_admin($item['title']), $item['page']);
  }

  $flippingbook['contents'] = $contents;
  
  $exists_query = 'SELECT nid FROM {flippingbook} WHERE nid = %d';
  if (db_result(db_query($exists_query, $flippingbook['nid']))) {
    drupal_write_record('flippingbook', $flippingbook, 'nid');
  }
  else{
    drupal_write_record('flippingbook', $flippingbook);
  }

  $form_state['redirect'] = 'node/'. $flippingbook['nid'];
  drupal_set_message(t('FlippingBook settings has been saved'));
}


function flippingbook_contents_form(&$form_state) {
  $form['contents'] = array(
    '#prefix' => '<div id="flippingbook-contents-wrapper">',
    '#suffix' => '</div>',
    '#theme' => 'flippingbook_contents_form',
    '#tree' => true,
  );
  
  if (!isset($form_state['values']['contents']) && !count($form_state['values']['contents'])) {
    $contents = array(array('title' => '', 'page' => '', 'weight' => 0));
  }
  else {
    $contents = $form_state['values']['contents'];
  }

  foreach ($contents as $index => $item) {
    $element = array(
      '#weight' => $item['weight'],
    );
    $element['page'] = array(
      '#type' => 'textfield',
      '#size' => 5,
      '#maxlength' => 5,
      '#default_value' => $item['page'],
      '#element_validate' => array('_flippingbook_validate_page_number'),
    );
    $element['title'] = array(
      '#type' => 'textfield',
      '#default_value' => $item['title'],
    );
    $element['weight'] = array(
      '#type' => 'weight', 
      '#default_value' => $item['weight'],
    );
    $element['remove'] = array(
      '#type' => 'checkbox',
    );
    
    $form['contents'][] = $element;
  }
  
  $form['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add new'),
    '#submit' => array('flippingbook_contents_add'),
    '#ahah' => array(
      'path' => 'flippingbook-contents-ahah',
      'wrapper' => 'flippingbook-contents-wrapper',
      'method' => 'replace',
    ),  
  );
  
  $form['remove'] = array(
    '#type' => 'submit',
    '#value' => t('Remove selected'),
    '#submit' => array('flippingbook_contents_remove'),
    '#ahah' => array(
      'path' => 'flippingbook-contents-ahah',
      'wrapper' => 'flippingbook-contents-wrapper',
      'method' => 'replace',
    ),    
  );
  
  return $form;
}

function _flippingbook_validate_page_number($element, &$form_state) {
  if (!is_numeric($element['#value'])) {
    form_error($element, t('Page must be a numerical value'));
  } 
}

function flippingbook_contents_add($form, &$form_state) {
  $form_state['values']['contents'][] = array('title' => '', 'page' => '', 'weight' => 10);
  $form_state['rebuild'] = true;
}

function flippingbook_contents_remove($form, &$form_state) {
  foreach ($form_state['values']['contents'] as $index => $item) {
    if ($item['remove']) {
      unset($form_state['values']['contents'][$index]);
    }
  }
  $form_state['rebuild'] = true;
}

/**
 * Theme contents form
 * 
 * @param array $form
 * @return string
 */
function theme_flippingbook_contents_form($form) {
  $header = array('', t('Page'), t('Title'), t('Weight'), t('Delete'));
  drupal_add_tabledrag('flippingbook-contents', 'order', 'sibling', 'item-weight');

  foreach (element_children($form) as $key) {
    // Add class to group weight fields for drag and drop.
    $form[$key]['weight']['#attributes']['class'] = 'item-weight';

    $row = array('');
    $row[] = drupal_render($form[$key]['page']);
    $row[] = drupal_render($form[$key]['title']);
    $row[] = drupal_render($form[$key]['weight']);
    $row[] = drupal_render($form[$key]['remove']);
    $rows[] = array('data' => $row, 'class' => 'draggable');
  }
  $output = theme('table', $header, $rows, array('id' => 'flippingbook-contents'));
  $output .= drupal_render($form);
  return $output;
}

/**
 * AHAH callback for contents form 
 */
function flippingbook_contents_ahah() {
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  // Get the form from the cache.
  $form = form_get_cache($form_build_id, $form_state);
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  // We will run some of the submit handlers so we need to disable redirecting.
  $form['#redirect'] = FALSE;
  // We need to process the form, prepare for that by setting a few internals
  // variables.
  $form['#post'] = $_POST;
  $form['#programmed'] = FALSE;
  $form_state['post'] = $_POST;
  // Build, validate and if possible, submit the form.
  drupal_process_form($form_id, $form, $form_state);
  // This call recreates the form relying solely on the form_state that the
  // drupal_process_form set up.
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);
  // Render the new output.
  $output = theme('status_messages') . drupal_render($form['contents_container']['contents']);

  drupal_json(array('status' => TRUE, 'data' => $output));  
}