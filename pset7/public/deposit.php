<?php
    //config
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("deposit_view.php", ["title" => "Deposit Cash"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $amount = $_POST["amount"];
        
        if ($amount > 5000)
        {
            apologize("Deposit Limit of \$5000 at a time");
        }
        else
        {
            if ($amount <= 0)
            {
                apologize("Must enter a positive value to deposit");
            }
            else
            {
                $deposit = CS50::query("UPDATE users SET cash = cash + ?", $amount);
                
                if ($deposit == 0)
                {
                    apologize("Deposit Failed");
                }
                else
                {
                    redirect("/");
                }
            }
            
        }
    }
?>