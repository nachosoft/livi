<?php
/**
 * Callback that decides if the user is new or not.
 */
function is_new_user(){
  global $user;
  $duser = user_load($user->uid);

  if ($duser->uid > 0){
    return false;
  }

  if ($duser->status > 0){
    return false;
  }
  return true;
}