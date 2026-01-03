<script>
    /**
     * @type {import('$lib/types').TemperatureSensor[]}
     */
    export let sensors;
</script>

<div class="card">
    {#each sensors as sensor}
        <div class="sensor">
            <span>{sensor.designator}</span>
            <span>{sensor.value}</span>
        </div>
    {/each}
</div>

<style>
    .card {
        display: flex;
        gap: 1rem;
        justify-content: space-around;
    }

    .sensor {
        display: flex;
        flex-direction: column;
    }
</style>
