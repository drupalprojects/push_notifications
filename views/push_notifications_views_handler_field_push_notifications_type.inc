<?php

/**
 * Field handler to display token type.
 * 
 * Allows for display of token type name or token type id.
 */
class push_notifications_views_handler_field_push_notifications_type extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    $options['type_format'] = array('default' => 'type_name');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['type_format'] = array(
      '#type' => 'select',
      '#title' => t('Output format'),
      '#options' => array(
        'type_name' => t('Token Type Name'),
        'type_id' => t('Token Type ID'),
      ),
      '#default_value' => $this->options['type_format'],
    );
    parent::options_form($form, $form_state);
  }

  function get_token_type_options(){
    return array(
      'type_name' => t('Token Type Name'),
      'type_id' => t('Token Type ID'),
    );
  }

  function render($values) {
    $token_type_id = $this->get_value($values);

    if ($this->options['type_format'] == 'type_id') {
      return $token_type_id;
    }

    // Show the token type name by default.
    return $this->get_token_type_name($token_type_id);
  }

  function get_token_type_name($type){
    // Build an array of types, as defined by the Push Notifications module.
    $valid_types = array(
      PUSH_NOTIFICATIONS_TYPE_ID_IOS => 'iOS',
      PUSH_NOTIFICATIONS_TYPE_ID_ANDROID => 'Android',
    );
    if (isset($valid_types[$type])){
      return $valid_types[$type];
    }
    return '';
  }
}
