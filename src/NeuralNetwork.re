/* This is the basic component. */
let component = ReasonReact.statelessComponent("NeuralNetwork");

/* Your familiar handleClick from ReactJS. This mandatorily takes the payload,
   then the `self` record, which contains state (none here), `handle`, `reduce`
   and other utilities */
let handleClick = (_event, _self) => Js.log("clicked!");

/* `make` is the function that mandatorily takes `children` (if you want to use
   `JSX). `message` is a named argument, which simulates ReactJS props. Usage:

   `<Page message="hello" />`

   Which desugars to

   `ReasonReact.element(Page.make(~message="hello", [||]))` */
let make = (~message, _children) => {
  ...component,
  render: self =>
    <div onClick={self.handle(handleClick)}>
      {ReasonReact.string(message)}
      <svg
        width="40"
        height="40"
        viewBox="0 0 20 20"
        xmlns="http://www.w3.org/2000/svg">
        <circle
          cx="10"
          cy="10"
          r="10"
          style={ReactDOMRe.Style.make(~fill="blue", ())}
          xmlns="http://www.w3.org/2000/svg"
        />
        <circle
          cx="10"
          cy="10"
          r="8"
          style={ReactDOMRe.Style.make(~fill="white", ())}
          xmlns="http://www.w3.org/2000/svg"
        />
      </svg>
    </div>,
};
