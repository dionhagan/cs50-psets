<form action="deposit.php" method="post">
    <h3>
        <?= htmlspecialchars("Please deposit up to \$5000") ?>
    </h3>
    <br>
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="amount" placeholder="Amount" type="number"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon"></span>
                Enter
            </button>
        </div>
    </fieldset>
</form>
