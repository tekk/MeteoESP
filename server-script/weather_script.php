<?php

  /* !!! TODO !!! Replace {your API key} with your own key and {your location} with station ID. In my case it was IBANSKBY8 */

  $json_string = file_get_contents("http://api.wunderground.com/api/{your API key}/conditions/q/pws:{your location}.json");
  $predpoved_json_string = file_get_contents("http://api.wunderground.com/api/{your API key}/forecast/q/pws:{your location}.json");
  $parsed_json = json_decode($json_string);
  $parsed_predpoved = json_decode($predpoved_json_string);
  
  $temp_c = $parsed_json->{'current_observation'}->{'temp_c'};
  $pressure = $parsed_json->{'current_observation'}->{'pressure_mb'};
  $weather = $parsed_json->{'current_observation'}->{'weather'};
  
  $forecast = $parsed_predpoved->{'forecast'}->{'simpleforecast'}->{'forecastday'};

  $p1_temperature_h = $forecast[0]->{'high'}->{'celsius'};
  $p1_temperature_l = $forecast[0]->{'low'}->{'celsius'};
  $p1_cond = $forecast[0]->{'conditions'};

  $p2_temperature_h = $forecast[1]->{'high'}->{'celsius'};
  $p2_temperature_l = $forecast[1]->{'low'}->{'celsius'};
  $p2_cond = $forecast[1]->{'conditions'};

  $p3_temperature_h = $forecast[2]->{'high'}->{'celsius'};
  $p3_temperature_l = $forecast[2]->{'low'}->{'celsius'};
  $p3_cond = $forecast[2]->{'conditions'};

  /* Print values for ESP8266 / Wemos. Semicolon delimited data, starting with "FCST:".  */
  
  echo "FCST:" . $temp_c . ";" . $pressure . ";" . $weather . ";" . $p1_temperature_h . ";" . $p1_temperature_l . ";" . $p1_cond . ";" . $p2_temperature_h . ";" . $p2_temperature_l . ";" . $p2_cond . ";" . $p3_temperature_h . ";" . $p3_temperature_l . ";" . $p3_cond . ";" . "\n";
?>
