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

OnClickConstruction(document.querySelectorAll(".shop-jaliconfig-options")[0], 'Standalone');
OnClickSupplier(document.querySelectorAll(".shop-jaliconfig-options")[1], 'LightYear');
//OnClickSize(document.querySelectorAll(".shop-jaliconfig-options")[2], '1ft x 1ft');

function OnClickConstruction(div, type)
{
  jalispecifications.construction = type;
  var index = undefined;

  document.querySelectorAll(".process-laser").forEach(element => {EnableButton(element);});

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

    document.querySelectorAll(".process-laser").forEach(element => {DisableButton(element);});
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
  jalispecifications.materialfront = undefined;
  jalispecifications.materialback = undefined;
  jalispecifications.thicknessfront = undefined;
  jalispecifications.thicknessback = undefined;
  jalispecifications.colorfront = undefined;
  jalispecifications.colorback = undefined;

  var index = undefined;
  if(type == 'CNC Laser 0.5mm')index = 0;
  if(type == 'CNC Router 3mm')index = 1;
  if(type == 'CNC Router 4mm')index = 2;
  if(type == 'CNC Router 6mm')index = 3;
  if(type == 'CNC Router 8mm')index = 4;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);

  for(var i=4;i<document.querySelectorAll(".shop-jaliconfig-options").length;i++)
    SelectButton(document.querySelectorAll(".shop-jaliconfig-options")[i].querySelectorAll(".shop-jaliconfig-button"), -1);  

  document.querySelectorAll(".front-acrylic").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-corian").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-acp").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-laminatedplywood").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-mdf").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-wpcpvcfoam").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-cementsheet").forEach(element => {EnableButton(element);});

  document.querySelectorAll(".front-1mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-2mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-3mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-4mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-5mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-6mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-8mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-10mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-12mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-15mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-18mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-20mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-25mm").forEach(element => {EnableButton(element);});

  document.querySelectorAll(".front-white").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-black").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-red").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-green").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-blue").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-orange").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-brown").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-yellow").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-transparent").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-white040").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-raw").forEach(element => {EnableButton(element);});

  if(index == 0)
  {
    document.querySelectorAll(".front-acp").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-laminatedplywood").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-cementsheet").forEach(element => {DisableButton(element);});
  }
  if(index == 1)
  {
    document.querySelectorAll(".front-cementsheet").forEach(element => {DisableButton(element);});
  }
  if(index == 2)
  {
    document.querySelectorAll(".front-cementsheet").forEach(element => {DisableButton(element);});
  }
  if(index == 3)
  {
  }
  if(index == 4)
  {
  } 
}

function OnClickMaterialFront(div, type)
{
  jalispecifications.materialfront = type;
  jalispecifications.thicknessfront = undefined;
  jalispecifications.colorfront = undefined;

  var index = undefined;
  if(type == 'Acrylic')index = 0;
  if(type == 'Corian')index = 1;
  if(type == 'ACP')index = 2;
  if(type == 'Laminated Plywood')index = 3;
  if(type == 'MDF')index = 4;
  if(type == 'WPC/PVC/Foam')index = 5;
  if(type == 'Cement Sheet')index = 6;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);

  SelectButton(document.querySelectorAll(".shop-jaliconfig-options")[5].querySelectorAll(".shop-jaliconfig-button"), -1);
  SelectButton(document.querySelectorAll(".shop-jaliconfig-options")[6].querySelectorAll(".shop-jaliconfig-button"), -1);
  SelectButton(document.querySelectorAll(".shop-jaliconfig-options")[11].querySelectorAll(".shop-jaliconfig-button"), -1);
  SelectButton(document.querySelectorAll(".shop-jaliconfig-options")[12].querySelectorAll(".shop-jaliconfig-button"), -1);
  SelectButton(document.querySelectorAll(".shop-jaliconfig-options")[13].querySelectorAll(".shop-jaliconfig-button"), -1);

  document.querySelectorAll(".front-1mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-2mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-3mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-4mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-5mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-6mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-8mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-10mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-12mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-15mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-18mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-20mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-25mm").forEach(element => {EnableButton(element);});

  document.querySelectorAll(".front-white").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-black").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-red").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-green").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-blue").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-orange").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-brown").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-yellow").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-transparent").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-white040").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".front-raw").forEach(element => {EnableButton(element);});

  if(index == 0)
  {
    document.querySelectorAll(".front-raw").forEach(element => {DisableButton(element);});
  }

  if(index == 1)
  {
    document.querySelectorAll(".front-1mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-2mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-3mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-4mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-5mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-8mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-10mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-15mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-18mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-20mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-25mm").forEach(element => {DisableButton(element);});

    document.querySelectorAll(".front-black").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-red").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-green").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-blue").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-orange").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-brown").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-yellow").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-transparent").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-white040").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-raw").forEach(element => {DisableButton(element);});
  }

  if(index == 2)
  {
    document.querySelectorAll(".front-1mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-2mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-4mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-5mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-6mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-8mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-10mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-12mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-15mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-18mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-20mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-25mm").forEach(element => {DisableButton(element);});

    document.querySelectorAll(".front-transparent").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-white040").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-raw").forEach(element => {DisableButton(element);});
  }

  if(index == 3)
  {
    document.querySelectorAll(".front-1mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-2mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-3mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-4mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-5mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-6mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-8mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-10mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-15mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-20mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-25mm").forEach(element => {DisableButton(element);});

    document.querySelectorAll(".front-transparent").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-white040").forEach(element => {DisableButton(element);});    
  }

  if(index == 4)
  {
    document.querySelectorAll(".front-1mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-2mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-3mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-4mm").forEach(element => {DisableButton(element);});

    document.querySelectorAll(".front-white").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-black").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-red").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-green").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-blue").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-orange").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-brown").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-yellow").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-transparent").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-white040").forEach(element => {DisableButton(element);});
  }

  if(index == 5)
  {
    document.querySelectorAll(".front-1mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-2mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-4mm").forEach(element => {DisableButton(element);});

    document.querySelectorAll(".front-black").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-red").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-green").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-blue").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-orange").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-brown").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-yellow").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-transparent").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-white040").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".front-raw").forEach(element => {DisableButton(element);});
  }

  if(index == 6)
    {
      document.querySelectorAll(".front-1mm").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-2mm").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-3mm").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-4mm").forEach(element => {DisableButton(element);});
  
      document.querySelectorAll(".front-white").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-black").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-red").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-green").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-blue").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-orange").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-brown").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-yellow").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-transparent").forEach(element => {DisableButton(element);});
      document.querySelectorAll(".front-white040").forEach(element => {DisableButton(element);});
    }

  if(jalispecifications.process == 'CNC Laser 0.5mm')document.querySelectorAll(".front-25mm").forEach(element => {DisableButton(element);});
  if(jalispecifications.process != 'CNC Laser 0.5mm')document.querySelectorAll(".front-1mm").forEach(element => {DisableButton(element);});
}

function OnClickMaterialBack(div, type)
{
  jalispecifications.materialback = type;
  jalispecifications.thicknessback = undefined;
  jalispecifications.colorback = undefined;
  
  var index = undefined;
  if(type == 'Acrylic')index = 0;
  if(type == 'Corian')index = 1;
  if(type == 'ACP')index = 2;
  if(type == 'Laminated Plywood')index = 3;
  if(type == 'MDF')index = 4;
  if(type == 'WPC/PVC/Foam')index = 5;
  if(type == 'Cement Sheet')index = 6;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);

  SelectButton(document.querySelectorAll(".shop-jaliconfig-options")[8].querySelectorAll(".shop-jaliconfig-button"), -1);
  SelectButton(document.querySelectorAll(".shop-jaliconfig-options")[9].querySelectorAll(".shop-jaliconfig-button"), -1);
  SelectButton(document.querySelectorAll(".shop-jaliconfig-options")[11].querySelectorAll(".shop-jaliconfig-button"), -1);
  SelectButton(document.querySelectorAll(".shop-jaliconfig-options")[12].querySelectorAll(".shop-jaliconfig-button"), -1);
  SelectButton(document.querySelectorAll(".shop-jaliconfig-options")[13].querySelectorAll(".shop-jaliconfig-button"), -1);

  document.querySelectorAll(".back-1mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-2mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-3mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-4mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-5mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-6mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-8mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-10mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-12mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-15mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-18mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-20mm").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-25mm").forEach(element => {EnableButton(element);});

  document.querySelectorAll(".back-white").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-black").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-red").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-green").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-blue").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-orange").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-brown").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-yellow").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-transparent").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-white040").forEach(element => {EnableButton(element);});
  document.querySelectorAll(".back-raw").forEach(element => {EnableButton(element);});

  if(index == 0)
  {
    document.querySelectorAll(".back-raw").forEach(element => {DisableButton(element);});
  }

  if(index == 1)
  {
    document.querySelectorAll(".back-1mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-2mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-3mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-4mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-5mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-8mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-10mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-15mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-18mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-20mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-25mm").forEach(element => {DisableButton(element);});

    document.querySelectorAll(".back-black").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-red").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-green").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-blue").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-orange").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-brown").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-yellow").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-transparent").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-white040").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-raw").forEach(element => {DisableButton(element);});
  }

  if(index == 2)
  {
    document.querySelectorAll(".back-1mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-2mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-4mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-5mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-6mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-8mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-10mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-12mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-15mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-18mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-20mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-25mm").forEach(element => {DisableButton(element);});

    document.querySelectorAll(".back-transparent").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-white040").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-raw").forEach(element => {DisableButton(element);});
  }

  if(index == 3)
  {
    document.querySelectorAll(".back-1mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-2mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-3mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-4mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-5mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-6mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-8mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-10mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-15mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-20mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-25mm").forEach(element => {DisableButton(element);});

    document.querySelectorAll(".back-transparent").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-white040").forEach(element => {DisableButton(element);});    
  }

  if(index == 4)
  {
    document.querySelectorAll(".back-1mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-2mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-3mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-4mm").forEach(element => {DisableButton(element);});

    document.querySelectorAll(".back-white").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-black").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-red").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-green").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-blue").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-orange").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-brown").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-yellow").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-transparent").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-white040").forEach(element => {DisableButton(element);});
  }

  if(index == 5)
  {
    document.querySelectorAll(".back-1mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-2mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-4mm").forEach(element => {DisableButton(element);});

    document.querySelectorAll(".back-black").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-red").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-green").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-blue").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-orange").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-brown").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-yellow").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-transparent").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-white040").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-raw").forEach(element => {DisableButton(element);});
  }

  if(index == 6)
  {
    document.querySelectorAll(".back-1mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-2mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-3mm").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-4mm").forEach(element => {DisableButton(element);});

    document.querySelectorAll(".back-white").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-black").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-red").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-green").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-blue").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-orange").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-brown").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-yellow").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-transparent").forEach(element => {DisableButton(element);});
    document.querySelectorAll(".back-white040").forEach(element => {DisableButton(element);});
  }

  if(jalispecifications.process == 'CNC Laser 0.5mm')document.querySelectorAll(".back-25mm").forEach(element => {DisableButton(element);});
  if(jalispecifications.process != 'CNC Laser 0.5mm')document.querySelectorAll(".back-1mm").forEach(element => {DisableButton(element);});
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
  if(type == 'White040')index = 9;
  if(type == 'RAW')index = 10;
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
  if(type == 'White040')index = 9;
  if(type == 'RAW')index = 10;
  SelectButton(div.querySelectorAll(".shop-jaliconfig-button"), index);
}

function OnChangeCuttingDepth(input)
{
  if(input.value > parseInt(jalispecifications.thicknessfront))input.value = parseInt(jalispecifications.thicknessfront) -2;
}

function SelectButton(divquerryselectorall, index)
{
  divquerryselectorall.forEach(element => {element.classList.remove("selected");});
  divquerryselectorall.forEach(element => {element.classList.add("unselected");});   
  if(index != -1)divquerryselectorall[index].classList.remove("unselected");
  if(index != -1)divquerryselectorall[index].classList.add("selected");
}
function EnableButton(button)
{
  button.classList.remove("selected");
  button.classList.remove("disabled");
  button.classList.add("unselected");
}
function DisableButton(button)
{
  button.classList.remove("selected");
  button.classList.remove("unselected");
  button.classList.add("disabled");
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