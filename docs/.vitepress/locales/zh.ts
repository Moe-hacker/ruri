import { defineConfig } from "vitepress";

export default defineConfig({
  themeConfig: {
    nav: [
      { text: "首页", link: "/zh/" },
      { text: "指南", link: "/zh/USAGE" },
    ],
    sidebar: sidebarGuide(),
    lastUpdated: {
      text: "上次更新",
    },
    editLink: {
      pattern: "https://github.com/Moe-hacker/ruri/edit/main/docs/:path",
      text: "编辑此页",
    },
    outline: {
      label: "页面导航",
      level: [2, 3],
    },
    docFooter: {
      prev: "上一页",
      next: "下一页",
    },
  },
});

function sidebarGuide() {
  return [
    {
      text: "文档",
      items: [
        { text: "快速开始", link: "/zh/Integration" },
        { text: "使用指南", link: "/zh/USAGE" },
        { text: "安全指南", link: "/zh/Security" },
        { text: "rurienv", link: "/zh/rurienv" },
        { text: "常见问题", link: "/zh/FAQ" },
        { text: "默认安全", link: "/zh/other_Security" },
        { text: "编译", link: "/zh/Build" },
      ],
    },
  ];
}
