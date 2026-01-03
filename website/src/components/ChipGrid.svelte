<script>
    /**
     * @type {number[][]}
     */
    export let rows;

    /**
     * @type {number}
     */
    export let columns;
</script>

<div class="card">
    <div class="grid" style:grid-template-columns="repeat({columns}, 1fr)">
        {#each rows as row}
            {#each row as number}
                <div data-number={number}>{number}</div>
            {/each}
        {/each}
    </div>
</div>

<style>
    .grid {
        display: grid;
    }
</style>
