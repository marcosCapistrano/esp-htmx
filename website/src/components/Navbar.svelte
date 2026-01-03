<script>
    import { page } from "$app/stores";

    $effect(() => {
        console.log($page.url.pathname);
    })
</script>

<header>
    <nav class="container">
        <a href="/boards" class:active={$page.url.pathname === "/boards/"}>
            Boards
        </a>

        <a href="/eeprom" class:active={$page.url.pathname === "/eeprom/"}>
            EEPROM
        </a>

        <a href="/config" class:active={$page.url.pathname === "/config/"}>
            Config
        </a>
    </nav>
</header>

<style>
    header {
        background-color: #000000;
    }

    nav {
        display: flex;
        font-size: var(--fs-200);
        text-transform: uppercase;
        gap: 1rem;
    }

    a {
        color: #ffffff;
        padding: 0.75rem 1.25rem;
    }

    a.active {
        color: #000000;
        background-color: #ffffff;
    }
</style>
