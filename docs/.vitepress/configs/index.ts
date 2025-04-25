import { defineConfig } from "vitepress";
export * from "./head";
import en from "./en";
import zh from "./zh";

export default defineConfig({
  locales: {
    root: {
      label: "English",
      lang: "en-US",
      ...en,
    },
    zh: {
      label: "简体中文",
      lang: "zh-CN",
      link: "/zh/",
      ...zh,
    },
  },
});
