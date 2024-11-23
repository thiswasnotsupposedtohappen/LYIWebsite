class Div
{
    constructor(_id)
    {
        this.div = undefined;
        this.id = _id;
        this.parent = undefined;
        this.classes = undefined;
        this.html = undefined;
    }
    Set(_parent,_classes,_html)
    {
        this.parent = _parent;
        this.classes = _classes;
        this.html = _html;
        this.div = document.createElement("div");
        this.div.id = this.id;
        this.div.innerHTML = this.html;
        this.div.classList = this.classes;
        this.parent.appendChild(this.div);
    }
};
class Button
{
  constructor(_id)
  {
    this.button = undefined;
    this.id = _id;
    this.parent = undefined;
    this.classes = undefined;
    this.html = undefined;
  }
  Set(_parent,_classes,_html)
  {
    this.parent = _parent;
    this.classes = _classes;
    this.html = _html;
    this.button = document.createElement("button");
    this.button.id = this.id;
    this.button.innerHTML = this.html;
    this.button.classList = this.classes;
    this.parent.appendChild(this.button);
    this.button.addEventListener("click", this.Onclick);
  }
  Onclick()
  {

  }  
};

var div_shop_jalispecification = new Div("shop-jalispecification");
div_shop_jalispecification.Set(document.body, "shop-jalispecification","");

var div_shop_jaliconfig_options = new Div("div_shop_jaliconfig_options");
div_shop_jaliconfig_options.Set(div_shop_jalispecification.div, "shop-jaliconfig-options", "");

var button_standalone = new Button("standalone");
var button_backsupported = new Button("backsupported");
var button_halfdepth = new Button("halfdepth");
button_standalone.Set(div_shop_jaliconfig_options.div,"shop-jaliconfig-button unselected","<h2>Standalone</h2>");
button_backsupported.Set(div_shop_jaliconfig_options.div,"shop-jaliconfig-button unselected","<h2>Back-Supported</h2>");
button_halfdepth.Set(div_shop_jaliconfig_options.div,"shop-jaliconfig-button unselected","<h2>Half-Depth</h2>");