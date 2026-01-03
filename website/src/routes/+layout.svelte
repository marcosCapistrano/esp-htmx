<script>
	import "../app.css";
	import favicon from "$lib/assets/favicon.svg";
	import Navbar from "../components/Navbar.svelte";

	let { children } = $props();
</script>

<svelte:head>
	<link rel="icon" href={favicon} />
</svelte:head>

<Navbar />
<main>
	{@render children()}
</main>

<style>
	main {
		padding-top: 2rem;
	}
</style>
