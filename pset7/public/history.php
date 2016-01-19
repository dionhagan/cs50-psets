<?php
    //config
    require("../includes/config.php");
    
    $logs = CS50::query("SELECT transaction, symbol, price, shares, time
                        FROM history WHERE user_id = ?", $_SESSION["id"]);
                        
    if (empty($logs))
    {
        htmlspecialchars("No transaction history logged");
    }
    else
    {
        $positions = [];
        
        foreach ($logs as $log)
        {
            $stock = lookup($log["symbol"]);
            if ($stock !== false)
            {
                $positions[] = [
                    "transaction" => $log["transaction"],
                    "time" => $log["time"],
                    "symbol" => $log["symbol"],
                    "shares" => $log["shares"],
                    "price" => $log["price"]
                ];
                
            }
        }
        render("history_view.php", ["title" => "History", "positions" => $positions]);
    }
?>