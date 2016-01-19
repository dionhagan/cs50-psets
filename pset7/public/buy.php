<?php
    //config
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy_form.php", ["title" => "Buy"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (!preg_match("/^\d+$/", $_POST["shares"]) || $_POST["shares"] == 0)
        {
            apologize("Shares must be a positive integer");
        }
        else
        {
            $buy = lookup($_POST["symbol"]);
            if ($buy["symbol"] == false)
            {
                apologize("Invalid symbol");
            }
            
            $user = CS50::query("SELECT cash FROM users WHERE id = ?", 
                                $_SESSION["id"]);
            //check cash query
            if ($user == 0)
            {
                apologize("Unable to find cash balance for user");
            }
            else
            {
                $cash = $user[0]["cash"];
                $cost = $buy["price"] * $_POST["shares"];
                
                // check for sufficient funds
                if ($cost > $cash)
                {
                    apologize("Insufficent funds for this purchase");
                }
                else
                {
                    $make_buy = CS50::query("INSERT INTO portfolios 
                                            (user_id, symbol, shares) 
                                            VALUES(?, ?, ?) 
                                            ON DUPLICATE KEY UPDATE 
                                            shares = shares + VALUES(shares)", 
                                            $_SESSION["id"], $buy["symbol"], 
                                            $_POST["shares"]);
                                            
                    // check for successful insertion                        
                    if ($make_buy == 0)
                    {
                        apologize("Unable to make purchase");
                    }
                    else
                    {
                        //if insertion successful, subtract cash from account
                        $take_cash = CS50::query("UPDATE users SET 
                                                 cash = cash - ? WHERE id = ?", 
                                                 $cost, $_SESSION["id"]);
                        
                        // undo all above if unable to take cash
                        if ($take_cash == 0)
                        {
                            $undo = CS50::query("UPDATE portfolios SET 
                                        shares = shares - ?
                                        WHERE symbol = ? AND user_id = ?");
                            
                            apologize("Unable to withdraw funds");
                        }
                        else
                        {
                            // log purchase in history
                            CS50::query("INSERT INTO history
                                (user_id, transaction, symbol, shares, price, time) 
                                VALUES(?, 'BUY', ?, ?, ?, NOW())",
                                $_SESSION["id"],
                                $buy["symbol"], 
                                $_POST["shares"], 
                                $buy["price"]);
                            redirect("/");
                        }
                    }
                }
            }
        }
    }
?>