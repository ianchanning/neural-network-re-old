# Getting started with ReasonML

> **Note:** This is effectively archived now. This was an attempt to port https://github.com/ianchanning/neural-network-js to ReasonML and ReasonReact (not ReScript...).
> There is an updated version (but still not complete) at https://github.com/ianchanning/neural-network-re

I write this as a stumbling fumbling guide for how to actually get started, when all you have is a Javascript and React backgroud with no knowledge of OCaml.

I'm using a combination of Fedora and Ubuntu.

Obviously start here: <https://reasonml.github.io/>

## Installation

I even went off the rails at this point because you need globally installed `bsb` support and you run into the sudo/not-sudo argument. Lots of people want you to install yarn/npm as non-sudo, but I do it as sudo.

The guide suggests that you do it without sudo and makes no mention of using sudo. So for people like me the documentation goes wrong from the very first step. This makes me sad.

The issue being that because I install `npm` with the Fedora package manager it's installed as sudo. So I need to run `sudo npm install -g` which is all fine and good, but some well meaning people rightly express that this should be avoided if possible, but in the case of Fedora this is unavoidable.

I wrote this all up in an [issue #2168](https://github.com/facebook/reason/issues/2168), with the [most relevant comment](https://github.com/facebook/reason/issues/2168#issuecomment-419392904) I made:

> In the npm troubleshooting guide and Grunt getting started guide they have the following advice for global installs:
>
> (You may need to prefix these commands with sudo, especially on Linux, or OS X if you installed Node using its default installer.)
>

I also hit the same problem with my ubuntu install.

If I run without `sudo` then the yarn add completes fine, but I get the following error if I try to run `bsb`:

> Command 'bsb' not found


So I have to run:

```
sudo yarn global add bs-platform
```

However now, you have to run bsb with sudo too. Otherwise you get the following error:

```
$ bsb -init hello -theme basic-reason
Making directory hello
npm WARN checkPermissions Missing write access to /usr/lib/node_modules
npm ERR! code EACCES
npm ERR! syscall access
npm ERR! path /usr/lib/node_modules
npm ERR! errno -13
npm ERR! Error: EACCES: permission denied, access '/usr/lib/node_modules'
npm ERR!  { [Error: EACCES: permission denied, access '/usr/lib/node_modules']
npm ERR!   stack:
npm ERR!    'Error: EACCES: permission denied, access \'/usr/lib/node_modules\'',
npm ERR!   errno: -13,
npm ERR!   code: 'EACCES',
npm ERR!   syscall: 'access',
npm ERR!   path: '/usr/lib/node_modules' }
npm ERR!
npm ERR! The operation was rejected by your operating system.
npm ERR! It is likely you do not have the permissions to access this file as the current user
npm ERR!
npm ERR! If you believe this might be a permissions issue, please double-check the
npm ERR! permissions of the file and its containing directories, or try running
npm ERR! the command again as root/Administrator.

npm ERR! A complete log of this run can be found in:
npm ERR!     /home/channi16/.npm/_logs/2020-05-02T11_56_03_062Z-debug.log
failed to run : npm link bs-platform
```

So you have to run:

```
sudo bsb -init hello -theme basic-reason
```

The problem with this is that it then creates the `hello` directory and all its contents as `root`. However you don't always need to use `sudo`. It seems like it's either the first time you use it, or perhaps when you use a new template. However after than you can run `bsb -init my-dir -theme basic-reason` without `sudo`. It's not even when using a new theme, you can init with un-used themes. It appears to be just the first time that you run `bsb -init` that it requires `sudo`.

## Editor plugins

The advice here is quite simple. Use VS Code unless you're like me and you want your freedom. In that case, if you use Vim, then you're in luck. I've wasted the 10 hours of time for you trying all the different combinations of plugins. See my previous blog post on [Using ReasonML with Vim / Neovim](https://ianchanning.wordpress.com/2020/08/14/using-reasonml-with-vim-neovim/).

## Initial coding of the demo project

I started with the demo project, this builds a `Demo.re` file to a Demo.bs.js file that can be run in node.

## React our way up the tree
I wanted to get display into the browser - but the basic demo is node only. I want raw JS.

The react example gives raw JS output - but it has to go through webpack.

Kinda annoying - but I guess the webpack converts the bucklescript node javascript into browser style javascript.

## Installing the demo

I ran the following to install the create-react demo:

```sh
bsb -theme react -init neural-network-re
```

## Running the demo

This installs a runnable demo. I of course hit an error when running the code:

```
[ian@localhost neural-network-re]$ npm run webpack

> neural-network-re@0.1.0 webpack /var/www/vhosts/reasonml/neural-network-re
> webpack -w

/var/www/vhosts/reasonml/neural-network-re/node_modules/webpack-cli/bin/config-yargs.js:89
describe: optionsSchema.definitions.output.properties.path.description,
                                           ^

TypeError: Cannot read property 'properties' of undefined
    at module.exports (/var/www/vhosts/reasonml/neural-network-re/node_modules/webpack-cli/bin/config-yargs.js:89:48)
    at /var/www/vhosts/reasonml/neural-network-re/node_modules/webpack-cli/bin/webpack.js:60:27
    at Object.<anonymous> (/var/www/vhosts/reasonml/neural-network-re/node_modules/webpack-cli/bin/webpack.js:515:3)
    at Module._compile (module.js:653:30)
    at Object.Module._extensions..js (module.js:664:10)
    at Module.load (module.js:566:32)
    at tryModuleLoad (module.js:506:12)
    at Function.Module._load (module.js:498:3)
    at Module.require (module.js:597:17)
    at require (internal/module.js:11:18)
npm ERR! code ELIFECYCLE
npm ERR! errno 1
npm ERR! neural-network-re@0.1.0 webpack: `webpack -w`
npm ERR! Exit status 1
npm ERR!
npm ERR! Failed at the neural-network-re@0.1.0 webpack script.
npm ERR! This is probably not a problem with npm. There is likely additional logging output above.

npm ERR! A complete log of this run can be found in:
npm ERR!     /home/ian/.npm/_logs/2018-11-26T22_05_12_616Z-debug.log
```

It's so frustrating when things don't 'just work'. Anyway it turns out to be [a webpack error that they fixed in](https://github.com/reasonml-community/reason-react-example/issues/45) the project back in October, the fix is to upgrade the webpack-cli version in the `package.json`.

Also it looks like I'm running an old version of bsb as it appears to install an old version of the project. My version has the stupid idea of trying to get hot reloading running first, rather than a simple build.

It looks like in the new version they simplify it and just run the regular build. At least then it's obvious that it's a webpack error rather than some weird compilation error. It's now just:

```sh
npm install
npm run build
npm run webpack
```

Then open `src/index.html`

That is pretty sweet! Got me a lovely simple index.html page up and running.

### Hot reloading

Now we can attempt the hot reloading.

```sh
npm run start
```

Then in a separate terminal:

```sh
npm run webpack
```

This then hot reloads the code - but it doesn't auto refresh the webpage - but at least I understand it.

## Steps towards a Neural Network

Now the first thing I want to try and do is get some SVG displaying, this isn't so simple because you need to do it in JSX that gets output to god knows what that eventually produces an SVG.

However via [a forum post](https://reasonml.chat/t/inline-svg-issue/702/2) there is a link for how to [display a basic SVG][1]. The slightly cryptic thing in there is that it doesn't display anything to the screen, it just creates the SVG in a variable.

I made some modifications to the demo code to it to output [a simple SVG circle][2] and then got the SVG displaying to the screen too

```reason
let m =
  <svg
    width="200"
    height="200"
    viewBox="0 0 200 200"
    xmlns="http://www.w3.org/2000/svg">
    <circle
      cx="5"
      cy="5"
      r="5"
      style=(ReactDOMRe.Style.make(~fill="black", ()))
      xmlns="http://www.w3.org/2000/svg"
    />
  </svg>;

ReactDOMRe.renderToElementWithId(m, "target");
```

The online tool (<https://reason.surge.sh>) is quite interesting because you get a lot more tooltips than I'm used to (this is because it has the language server plugged in). Also the fun with displaying the style attribute which was actually relatively painless. The [ReasonReact Docs for Style](https://reasonml.github.io/reason-react/docs/en/style.html) gave me the perfect example:

```reason
<div style=(
  ReactDOMRe.Style.make(~color="#444444", ~fontSize="68px", ())
)/>
```

That's as far as I've got for now. I've got an SVG circle appearing in the web version and I can use this in my local version without problem.

## Dom dom dom...

Ideally for my basic project I didn't want to use React. I have a simple HTML page that injects a few `<p>` tags and some `<svg>` circles. I do this easily enough with pure Javascript, so I shouldn't need React.

However trying it was very painful. Every DOM Element in Reason is an `Option`. So you have to spend your life with this 'could be null' chap and handle this could be null at every stage.

Basically it seems like the DOM is a type nightmare and trying to apply correct types to it produces your own personal hell.

```reason
  let _ =
    Document.getElementById("root", document)
    ->Belt.Option.map(_, Element.setInnerText(_, "Hello"));
  ();

  let el =
    document
    |> Document.createElement("p")
    |> Element.asHtmlElement
    |> unwrapUnsafely;
  /* let root = Document.getElementById("root", document); */
  document
  |> Document.getElementById("root")
  |> map(Element.appendChild(el));
```

The above is the equivalent of:

```javascript
var root = Document.getElementById("root");
root.innerText = "Hello";

var el = Document.createElement("p")
Document.getElementById("root").appendChild(el);
```

But trying to create and element, set it's innerText and then append it was beyond me after 8 hours of coding.

This is along with using the experimental (but interesting) library [bs-webapi](https://github.com/reasonml-community/bs-webapi-incubator), which is also [referred to](https://books.google.be/books?id=aqqWDwAAQBAJ&pg=PT97&lpg=PT97&dq=reasonml+document+getElementById&source=bl&ots=_7wCU1oFf7&sig=ACfU3U0AxGUhJoG6uRu6mJklIJQalhFiqw&hl=en&sa=X&ved=2ahUKEwjRpOb50JbpAhVI3aQKHe_vBAMQ6AEwA3oECAkQAQ#v=onepage&q=reasonml%20document%20getElementById&f=false) in a useful book on [Web Development with ReasonML](https://pragprog.com/book/reasonml/web-development-with-reasonml).

It's at this point I figure that ReasonReact seems to handle the Dom interaction better. I was able to get a fairly complex svg element displaying which is the hardest part. So perhaps just better to stick to that.

### Hidden pipes

Note that here they use the "reverse-application" operator `|>`. There's an excellent description about this in this [2ality blog post on ReasonML functions](https://2ality.com/2017/12/functions-reasonml.html#the-reverse-application-operator-(%7C%3E)):

> The operator `|>` is called *reverse-application operator* or *pipe operator*. It lets you chain function calls: `x |> f` is the same as `f(x)`. That may not look like much, but it is quite useful when combining function calls.

In the reason docs they refer to the `->` operator instead in the [Pipe First section](https://reasonml.github.io/docs/en/pipe-first):

> `->` is a convenient operator that allows you to "flip" your code inside-out. `a(b)` becomes `b->a`. It's a piece of syntax that doesn't have any runtime cost.

It seems that `->` is a subtly different operator from `|>` as the only reference to `|>` appears later on that page:

> We also cannot use the `|>` operator here, since the object comes first in the binding. But `->` works!

Frustratingly though the reason documentation just includes this mention of `|>` without actually saying what it is. The operator comes direct from OCaml, see ['Composition operators' in the `Stdlib` documentation](https://caml.inria.fr/pub/docs/manual-ocaml/libref/Stdlib.html#VAL(|%3E)).

Note that there is the similarity to the Javascript [pipeline operator](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Pipeline_operator).

### Belt

Also note the use of `Belt.Option.map` above. The [Belt module](https://bucklescript.github.io/bucklescript/api/Belt.html) is a community driven helper module:

> A stdlib shipped with BuckleScript This stdlib is still in beta but we encourage you to try it out and give us feedback. Motivation The motivation for creating such library is to provide BuckleScript users a better end-to-end user experience, since the original OCaml stdlib was not written with JS in mind.

### Easier DOM

Trying the latest `bsb -init my-react-app -theme react-hooks` includes the following snippet in `src/Index.re`:

```reason
  let title = document##createElement("div");
  title##className #= "containerTitle";
  title##innerText #= text;
```

which generates:

```javascript
  var title = document.createElement("div");
  title.className = "containerTitle";
  title.innerText = text;
```

Now this looks a *lot* simpler. But of course I've no idea what the `##` or `#=` operators do.


[1]: https://reason.surge.sh/?syntax=Reason&code=DYUwLgBAthC8BQEIB4DOA3A5opEDuAlgCZgAWsARAIwCsALBTkqSAZqWJQEwDsAHI1wR0BEHgBCAewAelAAwQFtOhF4CmEaVGAA7VJQ5gADgC4A9GbxWAdHgDM1yQCdMZrnI9mMmCgD4NyEQgAGao-kJIyMEEwGAgThpCshQAtABs1nwApIIRSACelOnWXDmJuIQk5NRUDmllecys7Jw1PNY0DY3RsfEAqjoEYPoUkgBGAFYgAMZgUgCuOkQEOphS0rl5xJQ9cU4pVH7lkcEgAPLBoeAQRIUUXBQQAPorlADKkvNO0yAAgsBGUgAQ0eThAqHmsUoqGBREkeAuVzAZ3me0OEDM4QiyDMu3iWMiZiCoSxOO8vgA3PAgA&canvas=200
[2]: https://reason.surge.sh/?syntax=Reason&code=DYUwLgBAthC8BQEIB4DOA3A5opEDuAlgCZgAWsARAEwAMNFOSpIBmpYlt9jE6BIeAEIB7AB6UaESVwhcGuCKKjAAdqkrswABwBcAej14jAOjwBmY8IBOmPVxp6MmCgD4eyAMYErH0DyQe4hQArPIKEB4AnpSh-hBWMWEKqGCRoLAAFABKIACGHmAAIgDyALI5xgDKqaDGULkA1iAZAH4AZgTAwJQARsD5DRQANBAZAJQTcUqq6hSaugZGeKYW1rb2jlhJEHpuSMibmC4A3PDwOflFZRVWICpEIFYAKsIAoqBQd2AA6gRkAJJEDJQEYUMC5GzgChjU5AA&canvas=615
