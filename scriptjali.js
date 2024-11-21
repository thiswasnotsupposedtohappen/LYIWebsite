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
    this.colorfront = undefined;
    this.colorback = undefined;
  }
}
var jalispecifications = new JaliSpecifications();

OnClickConstruction(document.querySelector(".shop-jaliconfig-options"), 'Standalone');

function OnClickConstruction(div, type)
{
  jalispecifications.construction = type;
  var index = undefined;
  if(type=='Standalone')
  {
    document.querySelector(".shop-jaliconfig-materialfront").style.display="grid"
    document.querySelector(".shop-jaliconfig-materialback").style.display="none"
    document.querySelector(".shop-jaliconfig-materialhalfdepth").style.display="none"
    index = 0;
  }
  if(type=='Back-Supported')
  {
    document.querySelector(".shop-jaliconfig-materialfront").style.display="grid"
    document.querySelector(".shop-jaliconfig-materialback").style.display="grid"
    document.querySelector(".shop-jaliconfig-materialhalfdepth").style.display="none"
    index = 1;
}
  if(type=='Half-Depth')
  {
    document.querySelector(".shop-jaliconfig-materialfront").style.display="none"
    document.querySelector(".shop-jaliconfig-materialback").style.display="none"
    document.querySelector(".shop-jaliconfig-materialhalfdepth").style.display="grid"
    index = 2;
  }

  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);
}

function OnClickSupplier(div, type)
{
  jalispecifications.supplier = type;
  var index = undefined;
  if(type == 'LightYear')index = 0;
  if(type == 'Customer')index = 1;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);
}

function OnClickSize(div, type)
{
  jalispecifications.size = type;
  var index = undefined;
  if(type == '1ft x 1ft')index = 0;
  if(type == '2ft x 1ft')index = 1;
  if(type == '2ft x 2ft')index = 2;
  if(type == '4ft x 1ft')index = 3;
  if(type == '4ft x 2ft')index = 4;
  if(type == '4ft x 3ft')index = 5;
  if(type == '4ft x 4ft')index = 6;
  if(type == '5ft x 2ft')index = 7;
  if(type == '5ft x 4ft')index = 8;
  if(type == '6ft x 2ft')index = 9;
  if(type == '6ft x 4ft')index = 10;
  if(type == '8ft x 4ft')index = 11;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);
}

function OnClickProcess(div, type)
{
  jalispecifications.process = type;
  var index = undefined;
  if(type == 'CNC Laser 0.5mm')index = 0;
  if(type == 'CNC Router 3mm')index = 1;
  if(type == 'CNC Router 4mm')index = 2;
  if(type == 'CNC Router 6mm')index = 3;
  if(type == 'CNC Router 8mm')index = 4;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);
}

function OnClickMaterialFront(div, type)
{
  jalispecifications.materialfront = type;
  var index = undefined;
  if(type == 'Acrylic')index = 0;
  if(type == 'Corian')index = 1;
  if(type == 'ACP')index = 2;
  if(type == 'Laminated Plywood')index = 3;
  if(type == 'MDF')index = 4;
  if(type == 'WPC/PVC/Foam')index = 5;
  if(type == 'Cement Sheet')index = 6;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);
}

function OnClickMaterialBack(div, type)
{
  jalispecifications.materialback = type;
  var index = undefined;
  if(type == 'Acrylic')index = 0;
  if(type == 'Corian')index = 1;
  if(type == 'ACP')index = 2;
  if(type == 'Laminated Plywood')index = 3;
  if(type == 'MDF')index = 4;
  if(type == 'WPC/PVC/Foam')index = 5;
  if(type == 'Cement Sheet')index = 6;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);
}

function OnClickThicknessFront(div, type)
{
  jalispecifications.thicknessfront = type;
  var index = undefined;
  
  if(type == '1mm')index = 0;
  if(type == '2mm')index = 1;
  if(type == '3mm')index = 2;
  if(type == '4mm')index = 3;
  if(type == '5mm')index = 4;
  if(type == '6mm')index = 5;
  if(type == '8mm')index = 6;
  if(type == '10mm')index = 7;
  if(type == '12mm')index = 8;
  if(type == '15mm')index = 9;
  if(type == '18mm')index = 10;
  if(type == '20mm')index = 11;
  if(type == '25mm')index = 12;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);
}

function OnClickThicknessBack(div, type)
{
  jalispecifications.thicknessback = type;
  var index = undefined;
  
  if(type == '1mm')index = 0;
  if(type == '2mm')index = 1;
  if(type == '3mm')index = 2;
  if(type == '4mm')index = 3;
  if(type == '5mm')index = 4;
  if(type == '6mm')index = 5;
  if(type == '8mm')index = 6;
  if(type == '10mm')index = 7;
  if(type == '12mm')index = 8;
  if(type == '15mm')index = 9;
  if(type == '18mm')index = 10;
  if(type == '20mm')index = 11;
  if(type == '25mm')index = 12;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);
}

function OnClickColorFront(div, type)
{
  jalispecifications.colorfront = type;
  var index = undefined;
  if(type == 'White')index = 0;
  if(type == 'Black')index = 1;
  if(type == 'Red')index = 2;
  if(type == 'Green')index = 3;
  if(type == 'Blue')index = 4;
  if(type == 'Orange')index = 5;
  if(type == 'Brown')index = 6;
  if(type == 'Yellow')index = 7;
  if(type == 'Transparent')index = 8;
  if(type == 'White 60% (040)')index = 9;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);
}

function OnClickColorBack(div, type)
{
  jalispecifications.colorback = type;
  var index = undefined;
  if(type == 'White')index = 0;
  if(type == 'Black')index = 1;
  if(type == 'Red')index = 2;
  if(type == 'Green')index = 3;
  if(type == 'Blue')index = 4;
  if(type == 'Orange')index = 5;
  if(type == 'Brown')index = 6;
  if(type == 'Yellow')index = 7;
  if(type == 'Transparent')index = 8;
  if(type == 'White 60% (040)')index = 9;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);
}

function SelectButton(divquerryselectorall, index)
{
  divquerryselectorall.forEach(element => {element.classList.remove("selected");});
  divquerryselectorall.forEach(element => {element.classList.add("unselected");});   
  divquerryselectorall[index].classList.remove("unselected");
  divquerryselectorall[index].classList.add("selected");
  console.log(jalispecifications)
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