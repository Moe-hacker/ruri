import { defineConfig } from "vitepress";
import configs, { head } from "./configs";

// https://vitepress.dev/reference/site-config
export default defineConfig({
  title: "Ruri Docs",
  head: head,
  locales: configs.locales,
  lastUpdated: true,
  metaChunk: true,
  ignoreDeadLinks: true,
  base: process.env.APP_BASE || "/",
  // cleanUrls: true, // Remove the '.html' suffix from the URL
  /*sitemap: {
    hostname: 'https://*.com/',
  },*/
  themeConfig: {
    externalLinkIcon: true,
    logo: {
      src: "/logo.png",
      alt: "Ruri",
    },
    siteTitle: "Ruri",
    socialLinks: [
      { icon: "github", link: "https://github.com/Moe-hacker/ruri" },
    ],
    footer: {
      message: "Released under the MIT License.",
      copyright: "Copyright © 2022-present Moe-hacker",
    },
  },
});
