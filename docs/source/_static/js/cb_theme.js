(function () {
  var STORAGE_KEY = "cb-docs-theme";
  var root = document.documentElement;

  function readStoredTheme() {
    try {
      var stored = window.localStorage.getItem(STORAGE_KEY);
      if (stored === "light" || stored === "dark") {
        return stored;
      }
    } catch (error) {
      return "light";
    }

    return "light";
  }

  function currentTheme() {
    return root.getAttribute("data-theme") === "dark" ? "dark" : "light";
  }

  function nextTheme(theme) {
    return theme === "dark" ? "light" : "dark";
  }

  function applyTheme(theme, persist) {
    root.setAttribute("data-theme", theme);
    root.style.colorScheme = theme;

    if (persist) {
      try {
        window.localStorage.setItem(STORAGE_KEY, theme);
      } catch (error) {
        /* Ignore storage failures. */
      }
    }

    syncToggleButton();
  }

  function syncToggleButton() {
    var button = document.querySelector(".cb-theme-toggle");
    if (!button) {
      return;
    }

    var theme = currentTheme();
    var targetTheme = nextTheme(theme);
    button.textContent = targetTheme === "dark" ? "Switch to dark mode" : "Switch to light mode";
    button.setAttribute("aria-label", button.textContent);
    button.setAttribute("aria-pressed", theme === "dark" ? "true" : "false");
    button.setAttribute("data-theme-target", targetTheme);
  }

  function handleToggleClick() {
    applyTheme(nextTheme(currentTheme()), true);
  }

  function mountToggle() {
    var sidebar = document.querySelector(".sphinxsidebarwrapper");
    if (!sidebar || sidebar.querySelector(".cb-theme-toggle-wrap")) {
      syncToggleButton();
      return;
    }

    var section = document.createElement("div");
    section.className = "cb-theme-toggle-wrap";

    var heading = document.createElement("h4");
    heading.textContent = "Theme";

    var button = document.createElement("button");
    button.type = "button";
    button.className = "cb-theme-toggle";
    button.addEventListener("click", handleToggleClick);

    section.appendChild(heading);
    section.appendChild(button);

    var logoBlock = sidebar.querySelector("p.logo");
    if (logoBlock && logoBlock.parentNode) {
      logoBlock.insertAdjacentElement("afterend", section);
    } else {
      sidebar.insertBefore(section, sidebar.firstChild);
    }

    syncToggleButton();
  }

  applyTheme(readStoredTheme(), false);

  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", mountToggle);
  } else {
    mountToggle();
  }
})();
