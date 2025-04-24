import { defineConfig } from "vitepress";
import en from "./en";
import zh from "./zh";

export default defineConfig({
  locales: {
    root: {
      label: "English",
      lang: "en-US",
      description: "Lightweight Linux container implementation",
      ...en,
    },
    zh: {
      label: "简体中文",
      lang: "zh-CN",
      link: "/zh/",
      description: "轻量级 Linux 容器实现",
      ...zh,
    },
  },
});
