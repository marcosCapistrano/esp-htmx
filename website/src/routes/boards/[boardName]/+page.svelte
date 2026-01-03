<script>
    import { page } from '$app/stores';
    import { getBoardConfig } from '$lib/boardConfigs';
    import ChipGrid from '../../../components/ChipGrid.svelte';
    import TemperatureBar from '../../../components/TemperatureBar.svelte';

    $: boardName = $page.params.boardName;
    $: config = getBoardConfig(boardName);

    // TODO: Fetch actual temperature data from backend
    // For now, using mock data
    /**
     * @type {import('$lib/types').TemperatureSensor[]}
     */
    $: sensors = config?.tempSensors.map((sensor) => ({
        designator: sensor.designator,
        value: 0, // Replace with actual backend data
    })) || [];
</script>

{#if config}
    <div class="container">
        <div class="header">
            <a href="/boards" class="card">GO BACK</a>
            <div class="board-indicator">{config.name}</div>
        </div>

        <TemperatureBar {sensors} />
        <ChipGrid rows={config.chipGrid} columns={config.gridColumns} />
    </div>
{:else}
    <div class="container">
        <p>Board "{boardName}" not found</p>
        <a href="/boards" class="card">GO BACK</a>
    </div>
{/if}

<style>
    .container {
        display: flex;
        flex-direction: column;
        gap: 1rem;
    }
    
    .header {
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 2rem;
        align-items: center;
    } 

    .board-indicator {
        color: var(--color-light);
        border: 1px solid var(--color-light);
        padding: 1em 1.5em;
    }
</style>