<?php

class tagging_ajax_suggest_base {

  private static $instance = null;

  /**
   * Return an instance of the class needed for the module to work in each Drupal version
   *
   * @return object
   */
  public static function instance() 
  {
    if(!tagging_ajax_suggest_base::$instance) {
      $impl = '';
      if(defined('VERSION')) {
        if(strpos(VERSION, '6') === 0) {
          $impl = 'tagging_ajax_suggest_d6';
          require_once(drupal_get_path('module', 'tagging_ajax_suggest') . '/tagging_ajax_suggest_d6.class.inc');
        } else {
          $impl = 'tagging_ajax_suggest_d7';
          require_once(drupal_get_path('module', 'tagging_ajax_suggest') . '/tagging_ajax_suggest_d6.class.inc');
          require_once(drupal_get_path('module', 'tagging_ajax_suggest') . '/tagging_ajax_suggest_d7.class.inc');
        }
      }
      tagging_ajax_suggest_base::$instance = new $impl();
    }
    
    return tagging_ajax_suggest_base::$instance;
  }
  
  /**
   * Implement hook_menu()
   *
   * Required so that no error pops up when the function is called in D7
   *
   * @return array
   */
  function hook_menu() {
    return array();
  }
}