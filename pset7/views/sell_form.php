<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="stock_to_sell">
                <option disabled="" selected="" value="">Symbol</option>
                <?php 
                    foreach ($options as $option)
                    {
                        print("<option id='stock_to_sell' value='".$option["symbol"]."'>".$option["symbol"]."</option>");
                    }
                ?>
            </select>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Sell
            </button>
        </div>
    </fieldset>
</form>