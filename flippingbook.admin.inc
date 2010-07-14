<?php

function flippingbook_admin_settings_form() {
  $settings    = array();
  $options = array();
  
  foreach (node_get_types() as $type) {
    list($src_field, $pages_field) = _flippingbook_get_fields($type->type);
    if ($src_field && $pages_field) {
      $options[$type->type] = $type->name;
    }
  }

  $form['flippingbook_node_types'] = array(
    '#title' => t('Node Types'),
    '#description' => t('Enable for these node types'),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => variable_get('flippingbook_node_types', array()),
  );
  
  $form['flippingbook_book_settings'] = array(
    '#title' => t('Default Book Settings'),
    '#type'  => 'fieldset',
    '#tree'  => true,
  );
  
  module_load_include('inc', 'flippingbook', 'flippingbook.edit_form');
  $form['flippingbook_book_settings'] += flippingbook_book_settings_form();
  $form['flippingbook_book_settings']['jsInitCode']['#type'] = 'textarea';
  
  return system_settings_form($form);
}