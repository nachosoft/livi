<?php
/**
 * Implements hook_block_info.
 */
function livi_users_block_info() {
  $blocks['livi_users_add'] = array(
    'info' => t('Formulario de Registro'), 
    'cache' => DRUPAL_NO_CACHE,
  );  
  return $blocks;
}

/**
 * Implements hook_block_view.
 */
function livi_users_block_view($delta = '') {
  $block = array(
    'content' => false, 
  );
  switch($delta) {
    case 'livi_users_add':
      if ( is_new_user() ) {
        $block['subject'] = t('Registro');
        $block['content'] = livi_users_add_block_content();
      }
      break;
  }
  return $block;
}

// Returns register form -> livi_users_add_form().
function  livi_users_add_block_content(){
  $output = drupal_get_form('livi_users_add_form');
  return $output;
}