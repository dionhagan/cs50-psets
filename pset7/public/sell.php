<?php
    // config
    require("../includes/config.php");
    
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", 
                        $_SESSION["id"]);

    if (empty($rows))
    {
        apologize("No stock shares found for this user");
    }
    else
    {
        if ($_SERVER["REQUEST_METHOD"] == "GET")
        {
            $options = [];
            
            foreach ($rows as $row)
            {
                $stock = lookup($row["symbol"]);
                if ($stock !== false)
                {
                    $options[] = [
                        "shares" => $row["shares"],
                        "symbol" => $row["symbol"]
                    ];
                }
            }
            render("sell_form.php", ["title" => "Sell", "options" => $options]);
        }
        else if ($_SERVER["REQUEST_METHOD"] == "POST")
        {
            // get stock to sell
            $sale = lookup($_POST["stock_to_sell"]);
            
            // get number of shares to sell
            $shares = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", 
                                      $_SESSION["id"], $sale["symbol"]);
            
            // delete the appropriate row from portfolios
            $make_sale = CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", 
                                     $_SESSION["id"], $sale["symbol"]);
                                     
            if ($make_sale !== 0)
            {
                // calculate amount to credit account
                $credit = $sale["price"] * $shares[0]["shares"];
                
                // query to add cash made from sale                        
                $add_cash = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", 
                                        $credit, $_SESSION["id"]);
                                        
                // if cash was successfully added, redirect to portfolio                        
                if ($add_cash == 0)
                {
                    apologize("Unable to credit account");
                }
                else
                {
                    // log sale in history
                    CS50::query("INSERT INTO history
                                (user_id, transaction, symbol, shares, price, time) 
                                VALUES(?, 'SELL', ?, ?, ?, NOW())",
                                $_SESSION["id"],
                                $sale["symbol"], 
                                $shares[0]["shares"], 
                                $sale["price"]);
                    redirect("/");   
                }
            }
            else
            {
                apologize("Unable to make sale");
            }
        }
    }
    

?>