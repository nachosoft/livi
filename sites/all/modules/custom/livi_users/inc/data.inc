<?php
/**
 * Get telephone number
 * Returns user 
 **/
function livi_users_load_by_tel($tel){

  if (!isset($tel)) {
    return false;
  }

  //$tel = 3111002427;

  $sql = sprintf("SELECT entity_id FROM field_data_field_celular WHERE field_celular_value = %d AND bundle = 'user'", $tel);
  $results = db_query($sql);
  $users = array();

  $row = $results->fetchAssoc();

  $uid = $row['entity_id'];


  if (!isset($uid)) {
    return false;
  }

  $duser = user_load($uid);

  return $duser;
}