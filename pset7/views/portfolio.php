<div>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price per Share</th>
                <th>Total</th>
            </tr>
        </thead>
        <tbody align="left">
            <?php foreach ($positions as $position): ?>
                <tr>
                    <td><?= $position["symbol"] ?></td>
                    <td><?= $position["name"] ?></td>
                    <td><?= $position["shares"] ?></td>
                    <td><?= "$".number_format($position["price"],3) ?></td>
                    <td><?= "$".number_format($position["total"],3) ?></td>
                </tr>
            <?php endforeach ?>
            <tr>
                <td>CASH</td>
                <td></td>
                <td></td>
                <td></td>
                <td><?= "$".$cash ?></td>
            </tr>
        </tbody>
    </table>
</div>
