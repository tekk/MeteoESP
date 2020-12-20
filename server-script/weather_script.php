<?php

  /* !!! TODO !!! Replace {your API key} with your own key and {yourStationId} with station ID from weather underground ones */
  /* {your lat DD.dd} with your latitude and {your lon DD.dd} with your longitude
  /* 20 Dec 2020 :Corrected for new APIs V2 and V3 api.weather.com (Obtain your own API key from wunderground
  
  You can obtain more information on weather API here : https://docs.google.com/document/d/1eKCnKXI9xnoMGRRzOL1xPCBihNV2rOet08qpE_gArAY/edit
  You can choose your forecast language changing the proper variable {lang} choosing from table : https://docs.google.com/document/d/13HTLgJDpsb39deFzk_YCQ5GoGoZCO_cRYzIxbwvgJLI/edit
  -> language=it-IT
  by Mattia - mattia.fiorini(at)gmail.com 
  */

  $json_string = file_get_contents("https://api.weather.com/v2/pws/observations/current?stationId={yourStationId}&format=json&units=m&apiKey={your API key}");

  $predpoved_json_string = file_get_contents("https://api.weather.com/v3/wx/forecast/daily/5day?geocode={your lat DD.dd},{your lon DD.dd}&format=json&units=m&language=it-IT&apiKey={your API key}");

  $parsed_json = json_decode($json_string);
  $parsed_predpoved = json_decode($predpoved_json_string);
  
  $forecast = $parsed_predpoved; 
  
  $temp_c = $parsed_json->{'observations'}[0]->{'metric'}->{'temp'};
  $pressure = $parsed_json->{'observations'}[0]->{'metric'}->{'pressure'};
  $weather = explode(".", $forecast->{'narrative'}[0]);
  $weather= $weather[0];


  $p1_temperature_h = $forecast->{'temperatureMax'}[1];
  $p1_temperature_l = $forecast->{'temperatureMin'}[1];
  $p1_cond = explode(".", $forecast->{'narrative'}[1]);
  $p1_cond= $p1_cond[0];

  $p2_temperature_h = $forecast->{'temperatureMax'}[2];
  $p2_temperature_l = $forecast->{'temperatureMin'}[2];
  $p2_cond = explode(".", $forecast->{'narrative'}[2]);
  $p2_cond= $p2_cond[0];
 
  $p3_temperature_h = $forecast->{'temperatureMax'}[3];
  $p3_temperature_l = $forecast->{'temperatureMin'}[3];
  $p3_cond = explode(".", $forecast->{'narrative'}[3]);
  $p3_cond= $p3_cond[0];

  /* Print values for ESP8266 / Wemos. Semicolon delimited data, starting with "FCST:".  */
  
  echo "FCST:" . $temp_c . ";" . $pressure . ";" . $weather . ";" . $p1_temperature_h . ";" . $p1_temperature_l . ";" . $p1_cond . ";" . $p2_temperature_h . ";" . $p2_temperature_l . ";" . $p2_cond . ";" . $p3_temperature_h . ";" . $p3_temperature_l . ";" . $p3_cond . ";" . "\n";
?>
