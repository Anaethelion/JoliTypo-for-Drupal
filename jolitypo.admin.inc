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
  $form['#submit'][] = 'jolitypo_admin_settings_submit';

  foreach ($languages as $language) {
    $form['jolitypo_'.$language->language] = array(
      '#type' => 'fieldset',
      '#title' => $language->name,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    foreach($features as $feature){
      $form['jolitypo_' . $language->language][$language->language.'_'.$feature] = array(
        '#type' => 'checkbox',
        '#title' => $feature,
      );
    }
  }

  return system_settings_form($form);
}

/**
 * Validation for jolitypo admin page
 */
function jolitypo_admin_settings_validation($form, &$form_state) {

}

/**
 * Submit for jolitypo admin page
 */
function jolitypo_admin_settings_submit($form, &$form_state) {
  var_dump($form_state['values']);die;

}

/**
 * Get available features to use with jolitypo
 * @return mixed
 */
function _jolitypo_get_available_features(){
  return array(
    'Ellipsis',
    'Dimension',
    'Dash',
    'EnglishQuotes',
    'CurlyQuote',
    'Hyphen',
    'Trademark',
    'FrenchQuotes',
    'FrenchNoBreakSpace',
    'GermanQuotes',
    'EnglishQuotes',
  );
}