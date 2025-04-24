import { defineConfig } from "vitepress";
import locales from "./locales";

// https://vitepress.dev/reference/site-config
export default defineConfig({
  title: "Ruri Docs",
  head: [["link", { rel: "icon", href: "/favicon.png" }]],
  locales: locales.locales,
  lastUpdated: true,
  metaChunk: true,
  /*cleanUrls: true,*/
  base: "/ruri/", // Used when deploy to a subpath
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
