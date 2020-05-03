[@bs.val] external document: Js.t({..}) = "document";
let nn = () => {
  let rand = (min, max) => Random.float(1.) *. (max -. min) +. min;
  Js.log(rand(2., 3.));
  Js.log(1. -> Random.float);
  let draw = () => {
    let drawP = (parent, text) => {
      let elem = document##createElement("p");
      elem##innerText #= text;
      let () = parent##appendChild(elem);
      ();
    };

    let root = document##createElement("div");
    root##id #= "root";
    drawP(root, "(0,0)");
    let () = document##body##appendChild(root);

    ();
  };
  draw();
};
nn();
