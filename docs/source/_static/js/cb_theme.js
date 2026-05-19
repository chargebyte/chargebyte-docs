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
    var label = targetTheme === "dark" ? "Switch to dark mode" : "Switch to light mode";
    var hiddenText = button.querySelector(".cb-visually-hidden");

    if (hiddenText) {
      hiddenText.textContent = label;
    }

    button.setAttribute("aria-label", label);
    button.setAttribute("title", label);
    button.setAttribute("aria-pressed", theme === "dark" ? "true" : "false");
    button.setAttribute("data-theme-target", targetTheme);
  }

  function handleToggleClick() {
    applyTheme(nextTheme(currentTheme()), true);
  }

  function mountToggle() {
    var relatedNav = document.querySelector(".related ul");
    if (!relatedNav || relatedNav.querySelector(".cb-theme-toggle-item")) {
      syncToggleButton();
      return;
    }

    var item = document.createElement("li");
    item.className = "cb-theme-toggle-item";

    var button = document.createElement("button");
    button.type = "button";
    button.className = "cb-theme-toggle";
    button.addEventListener("click", handleToggleClick);

    var hiddenText = document.createElement("span");
    hiddenText.className = "cb-visually-hidden";
    button.appendChild(hiddenText);

    item.appendChild(button);
    relatedNav.appendChild(item);

    syncToggleButton();
  }

  applyTheme(readStoredTheme(), false);

  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", mountToggle);
  } else {
    mountToggle();
  }
})();
