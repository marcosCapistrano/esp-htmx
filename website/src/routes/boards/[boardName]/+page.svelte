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

    // TODO: Update from backend when test starts
    let activeChips = 0;
</script>

{#if config}
    <div class="container">
        <div class="header">
            <a href="/boards" class="card">GO BACK</a>
            <div class="board-indicator">{config.name}</div>
        </div>

        <TemperatureBar {sensors} />
        <ChipGrid rows={config.chipGrid} columns={config.gridColumns} {activeChips} />

        <div class="actions">
            <button class="card">POWER ON</button>
            <button class="card">START TEST</button>
        </div>

        <footer class="footer">
            <p>AIO Tester</p>
        </footer>
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

    .actions {
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 2rem;
    }

    .actions button {
        cursor: pointer;
        border: none;
        font-size: var(--fs-100);
        text-transform: uppercase;
    }

    .footer {
        text-align: center;
        padding: 2rem 0;
        color: var(--color-light);
    }

    .footer p {
        margin: 0;
    }
</style>