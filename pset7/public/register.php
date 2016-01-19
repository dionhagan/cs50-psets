<?php

    // configuration
    require("../includes/config.php");
    //require("../includes/helpers.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]))
        {
            apologize("Must enter a username");
        }
        else if (empty($_POST["password"]))
        {
            apologize("Must enter a password");
        }
        else if ($_POST["confirmation"] !== $_POST["password"])
        {
            apologize("Password does not match confirmation");
        }
        
        // add user's info to the users database
        $new_user = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        
        // handle failure to create new user
        if ($new_user == 0)
        {
            apologize("Unable to create new user '?'", $_POST["username"]);
        }
        else
        {
            // if insert successful, create user session and send to index.php
            $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            $_SESSION["id"] = $id;
            redirect("index.php");
        }
        
    }

?>