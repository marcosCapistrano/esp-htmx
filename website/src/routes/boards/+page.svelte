<script>
    let boards = ["S19", "S19 Pro", "S19J Pro", "S19J Pro+"];
</script>

<div class="container grid">
    {#each boards as board}
        <a href={`/boards/${board}`} class="card">{board}</a> 
    {/each}
</div>

<style>
    .grid {
        display: grid;
        grid-template-columns: 1fr 1fr 1fr 1fr;
        gap: 2rem;
    }
</style>