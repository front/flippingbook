<?php

function flippingbook_book_settings_defaults() {
  $settings['bookWidth'] = 1000;
  $settings['bookHeight'] = 667;
  $settings['pageBackgroundColor'] = '0xc2c2c2'; // baksiden av boka
  $settings['backgroundColor'] = '0xb3b3b3';
  $settings['zoomUIColor'] = '0x919d6c';
//  $settings['useCustomCursors'] = false;
  $settings['dropShadowEnabled'] = false;
  $settings['zoomImageWidth'] = 1061;
  $settings['zoomImageHeight'] = 1472;
  $settings['flipSound'] = "sounds/02.mp3";
  $settings['flipCornerStyle'] = "first page only";
  $settings['zoomHintEnabled'] = false;
  $settings['jsInitCode'] = '';
  
  return $settings;
}


function flippingbook_book_settings_form($settings = null) {
  $defaults = flippingbook_book_settings_defaults();
  if (!is_array($settings) || count($settings) == 0) {
    $settings = variable_get('flippingbook_book_settings', $defaults); 
  }
  
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
  
  $descriptions['jsInitCode'] = t('Put javascript code for advanced FlippingBook initialization here');
  
  foreach ($settings as $key => $value) {
    $element_type = gettype($defaults[$key]) == 'boolean' ? 'checkbox' : 'textfield';
    $form[$key] = array(
      '#type' => $element_type,
      '#title' => $titles[$key],
      '#description' => @$descriptions[$key],
      '#default_value' => $value,
    );
  }
  
  return $form;
}

function flippingbook_edit_form(&$form_state, $node) {
  $form['#node'] = $node;
  
  if (is_array($node->flippingbook['contents'])) {
    $contents = $node->flippingbook['contents'];
    $contents_value = array();  
    
    foreach ($contents as $item) {
      $contents_value[] = join('|', $item);
    }
  }
  else {
    $contents_value = array();
  }

  $form['flippingbook'] = array(
    '#tree' => true,
  );
      
  $form['flippingbook']['contents'] = array(
    '#type' => 'textarea',
    '#title' => t('Table of contents'),
    '#default_value' => join("\n", $contents_value),
  );
  
  $form['flippingbook']['settings'] = array(
    '#tree' => true,
    '#type' => 'fieldset',
    '#title' => t('Custom Settings'),
    '#collapsible' => true,
  );
  
  $form['flippingbook']['settings'] += flippingbook_book_settings_form($node->flippingbook['settings']);
  $form['flippingbook']['settings']['jsInitCode']['#access'] = user_access('edit flippingbook advanced settings');
  $form['flippingbook']['settings']['jsInitCode']['#type'] = 'textarea';
  
  $form['submit'] = array(
    '#type' => 'submit',  
    '#value' => 'Save',
  );
                       
  return $form;
}

function flippingbook_edit_form_submit($form, &$form_state) {
  $flippingbook = $form_state['values']['flippingbook'];

  $contents = array();
  foreach(array_map('trim', explode("\n", $flippingbook['contents'])) as $item) {
    list($label, $page) = array_map('trim', explode('|', $item));
    $contents[] = array(filter_xss_admin($label), $page);
  }
  
  $flippingbook['contents'] = $contents;
  $flippingbook['nid'] = $form['#node']->nid;
  
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
