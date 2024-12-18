function EnableButtons(div)
{
  div.querySelectorAll("button").forEach(element => {element.classList.remove("disabled");});
  div.querySelectorAll("button").forEach(element => {element.classList.remove("selected");});
  div.querySelectorAll("button").forEach(element => {element.classList.add("unselected");});
}
function DisableButtons(div)
{
  div.querySelectorAll("button").forEach(element => {element.classList.remove("selected");});
  div.querySelectorAll("button").forEach(element => {element.classList.remove("unselected");});
  div.querySelectorAll("button").forEach(element => {element.classList.add("disabled");});
}
function SelectButton(div, index)
{
  div.querySelectorAll("button").forEach(element => {element.classList.remove("selected");});
  div.querySelectorAll("button").forEach(element => {element.classList.add("unselected");});
  if(index != -1)div.querySelectorAll("button")[index].classList.remove("unselected");
  if(index != -1)div.querySelectorAll("button")[index].classList.add("selected");
  if(typeof Draw !== 'undefined')Draw();
}
function EnableButton(button)
{
  button.classList.remove("selected");
  button.classList.remove("disabled");
  button.classList.add("unselected");
}
function DisableButton(button)
{
  if (button) 
  {
    button.classList.remove("selected");
    button.classList.remove("unselected");
    button.classList.add("disabled");
  }
}

class Item
{
    constructor(type, price, specifications)
    {
        this.type = type;
        this.price = price;
        this.specifications = specifications;
    }
}
class Cart
{
  constructor()
  {
    this.items = [];
  }
  Load()
  {
    var cartitems = JSON.parse(localStorage.getItem('cart'));
    if(cartitems != undefined)
    {
      this.items = cartitems;
      if(this.Count())
      {
        document.querySelector(".TopRibbonTextCartQuantity").innerHTML = this.Count();
        document.querySelector(".TopRibbonTextCartQuantity").style.display = "flex";
      }
    }
    else
    {
      document.querySelector(".TopRibbonTextCartQuantity").style.display = "none";
    }
  }
  Count()
  {
    return this.items.length;
  }
  Get(index)
  {
    return this.items[index];
  }
  Add(item)
  {
    this.items.push(item);
    localStorage.setItem('cart', JSON.stringify(this.items));
    document.querySelector(".TopRibbonTextCartQuantity").innerHTML = this.Count();
    document.querySelector(".TopRibbonTextCartQuantity").style.display = "flex";
  }
  Remove(index)
  {
    this.items.splice(index, 1);
    localStorage.setItem('cart', JSON.stringify(this.items));
    document.querySelector(".TopRibbonTextCartQuantity").innerHTML = this.Count();
    if(this.Count() == 0)document.querySelector(".TopRibbonTextCartQuantity").style.display = "none";
  }
};
var cart;
if(cart == null)
{
  cart = new Cart();
}
cart.Load();