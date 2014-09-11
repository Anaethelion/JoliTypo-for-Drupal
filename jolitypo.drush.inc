<?php
/**
 * Created by PhpStorm.
 * User: Anaethelion
 * Date: 28/08/2014
 * Time: 17:57
 */

/**
 * Implements drush_hook_pre_pm_enable()
 */
function drush_jolitypo_post_pm_enable() {
  // Get the list of modules being enabled; only download dependencies if our module name appears in the list
  $modules = drush_get_context('PM_ENABLE_MODULES');

  if (in_array('jolitypo', $modules) && !drush_get_option('skip')) {
    echo 'HEY ON INSTALLE !!';
    $jolitypo = libraries_info('jolitypo');
    $hyphenator = libraries_info('hyphenator');
    $urls = array(
      'jolitypo' => $jolitypo['download url'],
      'hyphenator' => $hyphenator['download url'],
    );

    foreach($urls as $name => $url){
      $path = drush_get_context('DRUSH_DRUPAL_ROOT');
      if (module_exists('libraries')) {
        if(!is_dir(libraries_get_path($name))) {
          $path = $path.'/sites/all/libraries/'.$name;
          $dest = $path;
          drush_mkdir($path);
        }
        $path .= '/' . libraries_get_path($name) . '/' . $name . '.tgz';
      }

      drush_download_file($url, $path) && drush_tarball_extract($path);
    }
  }
}