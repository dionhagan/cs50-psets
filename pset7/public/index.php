<?php

    // configuration
    require("../includes/config.php"); 
    
    // get rows of portfolio data for current user
    $rows = CS50::query("SELECT symbol, shares 
                        FROM portfolios WHERE user_id = ?", 
                        $_SESSION["id"]);
    
    if (empty($rows))
    {
        apologize("No stock shares found for this user");
    }
    else
    {
        $positions = [];
        
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
                $positions[] = [
                    "name" => $stock["name"],
                    "price" => $stock["price"],
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"],
                    "total" => $row["shares"] * $stock["price"]
                ];
                
            }
        }
        
        // get user's cash balance
        $user = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        // render portfolio
        render("portfolio.php", ["title" => "Portfolio", 
                                 "positions" => $positions, 
                                 "cash" => number_format($user[0]["cash"], 2)]);
    }
?>
