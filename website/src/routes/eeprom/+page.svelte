<script>
    // TODO: Will connect to backend for EEPROM operations
    // EEPROM clipboard holds 256 bytes of data
    let eepromData = ''; // Will hold 256 bytes from EEPROM
    let isReading = false;
</script>

<div class="container">
    <!-- EEPROM Clipboard - holds and displays 256 bytes -->
    <div class="eeprom-clipboard">
        {#if eepromData}
            <pre>{eepromData}</pre>
        {:else}
            <p>Press read to start reading the EEPROM</p>
        {/if}
    </div>

    <!-- Action Buttons -->
    <div class="actions">
        <button class="card">LOAD</button>
        <button class="card">SAVE</button>
        <button class="card">READ</button>
        <button class="card">WRITE</button>
    </div>

    <!-- Footer -->
    <footer class="footer">
        <p>AIO Tester</p>
    </footer>
</div>

<style>
    .container {
        display: flex;
        flex-direction: column;
        gap: 1rem;
    }

    .eeprom-clipboard {
        background-color: var(--color-dark);
        color: var(--color-light);
        padding: 2rem;
        min-height: 400px;
        max-height: 600px;
        overflow-y: auto;
        display: flex;
        align-items: center;
        justify-content: center;
    }

    .eeprom-clipboard p {
        font-size: var(--fs-200);
    }

    .eeprom-clipboard pre {
        font-family: monospace;
        font-size: var(--fs-50);
        white-space: pre;
        overflow-x: auto;
        width: 100%;
        margin: 0;
        line-height: 1.5;
    }

    .actions {
        display: grid;
        grid-template-columns: 1fr 1fr;
        grid-template-rows: 1fr 1fr;
        gap: 1rem;
    }

    .actions button {
        cursor: pointer;
        border: none;
        font-size: var(--fs-200);
        text-transform: uppercase;
        padding: 2rem;
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
