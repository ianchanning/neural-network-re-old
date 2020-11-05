// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/legacy/ReasonReact.bs.js");

var component = ReasonReact.reducerComponent("Example");

function make(greeting, _children) {
  return {
          debugName: component.debugName,
          reactClassInternal: component.reactClassInternal,
          handedOffState: component.handedOffState,
          willReceiveProps: component.willReceiveProps,
          didMount: component.didMount,
          didUpdate: component.didUpdate,
          willUnmount: component.willUnmount,
          willUpdate: component.willUpdate,
          shouldUpdate: component.shouldUpdate,
          render: (function (self) {
              var message = "You've clicked this " + (String(self.state.count) + " times(s)");
              return React.createElement("div", undefined, React.createElement("button", {
                              onClick: (function (_event) {
                                  return Curry._1(self.send, /* Click */0);
                                })
                            }, message), React.createElement("button", {
                              onClick: (function (_event) {
                                  return Curry._1(self.send, /* Toggle */1);
                                })
                            }, "Toggle greeting"), self.state.show ? greeting : null);
            }),
          initialState: (function (param) {
              return {
                      count: 0,
                      show: true
                    };
            }),
          retainedProps: component.retainedProps,
          reducer: (function (action, state) {
              if (action) {
                return /* Update */Block.__(0, [{
                            count: state.count,
                            show: !state.show
                          }]);
              } else {
                return /* Update */Block.__(0, [{
                            count: state.count + 1 | 0,
                            show: state.show
                          }]);
              }
            }),
          jsElementWrapped: component.jsElementWrapped
        };
}

exports.component = component;
exports.make = make;
/* component Not a pure module */
