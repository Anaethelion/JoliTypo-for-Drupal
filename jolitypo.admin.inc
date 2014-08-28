<?php
/**
 * Created by PhpStorm.
 * User: anaethelion
 * Date: 01/12/13
 * Time: 17:48
 */

/**
 * return settings array
 */
function jolitypo_admin_settings($form, &$form_state) {
  $languages = language_list();

  $features = _jolitypo_get_available_features();

  $form['#validate'][] = 'jolitypo_admin_settings_validation';

  foreach ($languages as $language) {
    $values = array_flip(variable_get('jolitypo_' . $language->language));

    $form['jolitypo_' . $language->language] = array(
      '#type' => 'fieldset',
      '#title' => $language->name,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['jolitypo_' . $language->language]['jolitypo_' . $language->language . '_titles'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use on titles'),
      '#default_value' => array_key_exists('titles', $values),
      '#suffix' => '<br/>',
    );

    foreach ($features as $feature => $default_value) {
      $form['jolitypo_' . $language->language]['jolitypo_' . $language->language . '_' . $feature] = array(
        '#type' => 'checkbox',
        '#title' => $feature,
        '#default_value' => array_key_exists($feature, $values),
      );
    }
  }

  return system_settings_form($form);
}

/**
 * Validation for jolitypo admin page
 */
function jolitypo_admin_settings_validation($form, &$form_state) {
  $languages = language_list();
  $next_values = array();

  form_state_values_clean($form_state);
  $values = array_keys($form_state['values'], 1);

  //sort results by language
  foreach ($languages as $language) {
    foreach ($values as $value) {
      if (strpos($value, 'jolitypo_' . $language->language) !== FALSE) {
        $next_values['jolitypo_' . $language->language][] = str_replace('jolitypo_' . $language->language . '_', '', $value);
      }
    }
  }

  //search for errors
  foreach ($next_values as $values) {
    $multiplequotes = 0;
    foreach ($values as $value) {
      if (strpos($value, 'Quotes')) {
        $multiplequotes++;
        if ($multiplequotes > 1) {
          form_set_error($value, t('Only one quote par language can be specified : ' . $value));
          return;
        }
      }
    }
  }

  $form_state['values'] = $next_values;

}

/**
 * Get available features to use with jolitypo
 * @return mixed
 */
function _jolitypo_get_available_features() {
  return array(
    'Ellipsis' => 1,
    'Dimension' => 1,
    'Dash' => 1,
    'CurlyQuote' => 1,
    'Hyphen' => 1,
    'Trademark' => 1,
    'FrenchQuotes' => 0,
    'FrenchNoBreakSpace' => 0,
    'GermanQuotes' => 0,
    'EnglishQuotes' => 0,
  );
}