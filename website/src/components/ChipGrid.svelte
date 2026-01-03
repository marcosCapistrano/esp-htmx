<script>
    /**
     * @type {number[][]}
     */
    export let rows;

    /**
     * @type {number}
     */
    export let columns;

    /**
     * @type {number}
     */
    export let activeChips = 0;
</script>

<div class="card">
    <div class="grid" style:grid-template-columns="repeat({columns}, 1fr)">
        {#each rows as row}
            {#each row as number}
                <div
                    class="chip"
                    class:active={number > 0 && number <= activeChips}
                    class:inactive={number > activeChips}
                    class:empty={number <= 0}
                    data-number={number}
                >
                    {number > 0 ? number : ''}
                </div>
            {/each}
        {/each}
    </div>
</div>

<style>
    .card {
        background-color: #000000;
        padding: 1rem;
    }

    .grid {
        display: grid;
        gap: 0.5rem;
    }

    .chip {
        /* aspect-ratio: 1; */
        display: flex;
        align-items: center;
        justify-content: center;
        border: 2px solid;
        border-radius: 4px;
        padding: 0.5em;
        font-size: var(--fs-100);
    }

    .chip.active {
        border-color: #00ff00;
        color: var(--color-white);
        background-color: var(--color-dark);
    }

    .chip.inactive {
        border-color: #444444;
        color: var(--color-light);
        background-color: var(--color-dark);
    }

    .chip.empty {
        border-color: transparent;
        visibility: hidden;
    }
</style>
