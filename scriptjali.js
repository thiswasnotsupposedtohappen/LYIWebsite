class JaliSpecifications
{
  constructor()
  {
    this.construction = "Standalone";
    this.supplier = "LYI";
    this.size = "1x1"
    this.process = "L";
    this.materialfront = "Acrylic";
    this.materialback = "Acrylic";
    this.thicknessfront = "2";
    this.thicknessback = "2";
  }
}
var jalispecifications = new JaliSpecifications();


function OnClickConstruction(type)
{
  if(type=='Standalone')
  {
    document.querySelectorAll(".shop-jaliconfig-materialfront")[0].style.display="grid"
    document.querySelectorAll(".shop-jaliconfig-materialback")[0].style.display="none"
    document.querySelectorAll(".shop-jaliconfig-materialhalfdepth")[0].style.display="none"
  }
  else if(type=='Back-Supported')
  {
    document.querySelectorAll(".shop-jaliconfig-materialfront")[0].style.display="grid"
    document.querySelectorAll(".shop-jaliconfig-materialback")[0].style.display="grid"
    document.querySelectorAll(".shop-jaliconfig-materialhalfdepth")[0].style.display="none"
}
  else if(type=='Half-Depth')
  {
    document.querySelectorAll(".shop-jaliconfig-materialfront")[0].style.display="none"
    document.querySelectorAll(".shop-jaliconfig-materialback")[0].style.display="none"
    document.querySelectorAll(".shop-jaliconfig-materialhalfdepth")[0].style.display="grid"
  }
}
OnClickConstruction(jalispecifications.construction);

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