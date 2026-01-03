import adapter from '@sveltejs/adapter-static';

/** @type {import('@sveltejs/kit').Config} */
const config = {
	kit: {
		adapter: adapter({
			pages: 'build',
			assets: 'build',
			fallback: 'index.html', // Critical for Single Page Apps (SPA)
			precompress: false, // Set to true if your ESP32 webserver supports gzip
			strict: true
		})
	}
};

export default config;
