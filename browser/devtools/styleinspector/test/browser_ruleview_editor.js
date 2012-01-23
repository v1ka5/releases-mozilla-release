/* vim: set ts=2 et sw=2 tw=80: */
/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

let tempScope = {}
Cu.import("resource:///modules/devtools/CssRuleView.jsm", tempScope);
let CssRuleView = tempScope.CssRuleView;
let _ElementStyle = tempScope._ElementStyle;
let _editableField = tempScope._editableField;

let doc = content.document;

function expectDone(aValue, aCommit, aNext)
{
  return function(aDoneValue, aDoneCommit) {
    dump("aDoneValue: " + aDoneValue + " commit: " + aDoneCommit + "\n");

    is(aDoneValue, aValue, "Should get expected value");
    is(aDoneCommit, aDoneCommit, "Should get expected commit value");
    aNext();
  }
}

function clearBody()
{
  doc.body.innerHTML = "";
}

function createSpan()
{
  let span = doc.createElement("span");
  span.setAttribute("tabindex", "0");
  span.textContent = "Edit Me!";
  doc.body.appendChild(span);
  return span;
}

function testReturnCommit()
{
  clearBody();
  let span = createSpan();
  _editableField({
    element: span,
    initial: "explicit initial",
    start: function() {
      is(span.inplaceEditor.input.value, "explicit initial", "Explicit initial value should be used.");
      span.inplaceEditor.input.value = "Test Value";
      EventUtils.sendKey("return");
    },
    done: expectDone("Test Value", true, testBlurCommit)
  });
  span.focus();
}

function testBlurCommit()
{
  clearBody();
  let span = createSpan();
  _editableField({
    element: span,
    start: function() {
      is(span.inplaceEditor.input.value, "Edit Me!", "textContent of the span used.");
      span.inplaceEditor.input.value = "Test Value";
      span.inplaceEditor.input.blur();
    },
    done: expectDone("Test Value", true, testAdvanceCharCommit)
  });
  span.focus();
}

function testAdvanceCharCommit()
{
  clearBody();
  let span = createSpan();
  _editableField({
    element: span,
    advanceChars: ":",
    start: function() {
      let input = span.inplaceEditor.input;
      for each (let ch in "Test:") {
        EventUtils.sendChar(ch);
      }
    },
    done: expectDone("Test", true, testEscapeCancel)
  });
  span.focus();
}

function testEscapeCancel()
{
  clearBody();
  let span = createSpan();
  _editableField({
    element: span,
    initial: "initial text",
    start: function() {
      span.inplaceEditor.input.value = "Test Value";
      EventUtils.sendKey("escape");
    },
    done: expectDone("initial text", false, finishTest)
  });
  span.focus();
}


function finishTest()
{
  doc = null;
  gBrowser.removeCurrentTab();
  finish();
}


function test()
{
  waitForExplicitFinish();
  gBrowser.selectedTab = gBrowser.addTab();
  gBrowser.selectedBrowser.addEventListener("load", function(evt) {
    gBrowser.selectedBrowser.removeEventListener(evt.type, arguments.callee, true);
    doc = content.document;
    waitForFocus(testReturnCommit, content);
  }, true);

  content.location = "data:text/html,inline editor tests";
}
