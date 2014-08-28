<?php
/**
 * Created by PhpStorm.
 * User: Anaethelion
 * Date: 28/08/2014
 * Time: 17:57
 */

function jolitypo_drush_command() {
  $items['download-libs'] = array(
    'description' => 'Download libraries for JoliTypo',
    'arguments' => array(),
    'aliases' => 'jdl',
  );
}