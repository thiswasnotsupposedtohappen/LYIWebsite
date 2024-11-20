class JaliSpecifications
{
  constructor()
  {
    this.construction = undefined;
    this.supplier = undefined;
    this.size = undefined;
    this.process = undefined;
    this.materialfront = undefined;
    this.materialback = undefined;
    this.thicknessfront = undefined;
    this.thicknessback = undefined;
  }
}
var jalispecifications = new JaliSpecifications();


function OnClickConstruction(div, type)
{
  if(type=='Standalone')
  {
    jalispecifications.construction = 'Standalone';
    document.querySelector(".shop-jaliconfig-materialfront").style.display="grid"
    document.querySelector(".shop-jaliconfig-materialback").style.display="none"
    document.querySelector(".shop-jaliconfig-materialhalfdepth").style.display="none"
    div.querySelectorAll(".shop-jaliconfig-button").forEach(element => {element.style.backgroundColor="rgb(146, 228, 255)";});
    div.querySelectorAll(".shop-jaliconfig-button")[0].style.backgroundColor="rgb(255, 153, 0)";
  }
  if(type=='Back-Supported')
  {
    jalispecifications.construction = 'Back-Supported';
    document.querySelector(".shop-jaliconfig-materialfront").style.display="grid"
    document.querySelector(".shop-jaliconfig-materialback").style.display="grid"
    document.querySelector(".shop-jaliconfig-materialhalfdepth").style.display="none"
    div.querySelectorAll(".shop-jaliconfig-button").forEach(element => {element.style.backgroundColor="rgb(146, 228, 255)";});
    div.querySelectorAll(".shop-jaliconfig-button")[1].style.backgroundColor="rgb(255, 153, 0)";
}
  if(type=='Half-Depth')
  {
    jalispecifications.construction = 'Half-Depth';
    document.querySelector(".shop-jaliconfig-materialfront").style.display="none"
    document.querySelector(".shop-jaliconfig-materialback").style.display="none"
    document.querySelector(".shop-jaliconfig-materialhalfdepth").style.display="grid"
    div.querySelectorAll(".shop-jaliconfig-button").forEach(element => {element.style.backgroundColor="rgb(146, 228, 255)";});
    div.querySelectorAll(".shop-jaliconfig-button")[2].style.backgroundColor="rgb(255, 153, 0)";
  }
}

function OnClickSupplier(div, type)
{
  if(type=='LightYear')
  {
    jalispecifications.supplier = 'LightYear';
    div.querySelectorAll(".shop-jaliconfig-button").forEach(element => {element.style.backgroundColor="rgb(146, 228, 255)";});
    div.querySelectorAll(".shop-jaliconfig-button")[0].style.backgroundColor="rgb(255, 153, 0)";
  }
  if(type=='Customer')
  {
    jalispecifications.supplier = 'Customer';
    div.querySelectorAll(".shop-jaliconfig-button").forEach(element => {element.style.backgroundColor="rgb(146, 228, 255)";});
    div.querySelectorAll(".shop-jaliconfig-button")[1].style.backgroundColor="rgb(255, 153, 0)";
  }
}

var shop_menu_innerhtml = document.querySelector(".shop-menu").innerHTML;
for(var i=1;i<=30;i++)
{
  shop_menu_innerhtml += `
  <div class="shop-menu-items">
    <a href="shop-jali-build.html?design=MandirDesign-`+i+`"><img class="shop-menu-items-img" src="images/Decorative Jali/Mandir Back/`+i+`.jpg"></a><br>
    <h2>MandirDesign-`+i+`</h2>
  </div>
  `;
}  
for(var i=1;i<=20;i++)  
{
  shop_menu_innerhtml += `
  <div class="shop-menu-items">
    <a href="shop-jali-build.html?design=MandirSide-`+i+`"><img class="shop-menu-items-img" src="images/Decorative Jali/Mandir side/`+i+`.jpg"></a><br>
    <h2>MandirSide-`+i+`</h2>
  </div>
  `;
}
for(var i=1;i<=280;i++)
{
  shop_menu_innerhtml += `
  <div class="shop-menu-items">
    <a href="shop-jali-build.html?design=JaliPartition-`+i+`"><img class="shop-menu-items-img" src="images/Decorative Jali/Jali/`+i+`.jpg"></a><br>
    <h2>JaliPartition-`+i+`</h2>
  </div>
  `;
}
document.querySelector(".shop-menu").innerHTML = shop_menu_innerhtml;