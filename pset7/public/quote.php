<?php

    // config
    require("../includes/config.php");
    
    //process GET and POST requests
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("quote_form.php", ["title" => "Quotes"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        
        if ($stock["symbol"] == false)
        {
            apologize("Invalid symbol");
        }
        else
        {
            //print_r($stock);
            render("quote_view.php", ["symbol" => $stock["symbol"], 
                                      "name" => $stock["name"], 
                                      "price" => number_format($stock["price"], 3)]);
        }
    }
?>