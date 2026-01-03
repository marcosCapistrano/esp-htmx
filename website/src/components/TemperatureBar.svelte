<script>
    /**
     * @type {import('$lib/types').TemperatureSensor[]}
     */
    export let sensors;
</script>

<div class="card">
    {#each sensors as sensor}
        <div class="sensor">
            <span class="designator">{sensor.designator}</span>
            <span class="value">{sensor.value} °C</span>
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
        align-items: center;
    }

    .designator::before {
        content: "● ";
        color: #00ff00;
    }
</style>
