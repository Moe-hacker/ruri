import { defineConfig } from "vitepress";

export default defineConfig({
  description: "Lightweight Linux container implementation",
  themeConfig: {
    nav: [
      { text: "Home", link: "/" },
      { text: "Guide", link: "/USAGE" },
    ],
    sidebar: {
      "/": sidebar(),
    },
    lastUpdated: {
      text: "Last Updated",
    },
    editLink: {
      pattern: "https://github.com/Moe-hacker/ruri/edit/main/docs/:path",
      text: "Edit this page",
    },
    outline: {
      label: "Page Navigation",
      level: [2, 3],
    },
    docFooter: {
      prev: "Previous page",
      next: "Next page",
    },
  },
});

function sidebar() {
  return [
    {
      text: "Documentation",
      items: [
        { text: "Integration", link: "/Integration" },
        { text: "Usage Guide", link: "/USAGE" },
        { text: "Security", link: "/Security" },
        { text: "rurienv", link: "/rurienv" },
        { text: "FAQ", link: "/FAQ" },
        { text: "Default Security", link: "/other_Security" },
        { text: "Build", link: "/Build" },
      ],
    },
  ];
}
