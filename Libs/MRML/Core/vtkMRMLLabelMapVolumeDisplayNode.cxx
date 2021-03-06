/*=auto=========================================================================

Portions (c) Copyright 2005 Brigham and Women\"s Hospital (BWH) All Rights Reserved.

See COPYRIGHT.txt
or http://www.slicer.org/copyright/copyright.txt for details.

Program:   3D Slicer
Module:    $RCSfile: vtkMRMLVolumeDisplayNode.cxx,v $
Date:      $Date: 2006/03/17 15:10:10 $
Version:   $Revision: 1.2 $

=========================================================================auto=*/

#include "vtkMRMLLabelMapVolumeDisplayNode.h"
#include "vtkMRMLProceduralColorNode.h"
#include "vtkMRMLScene.h"

// VTK includes
#include <vtkImageData.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>
#include <vtkObjectFactory.h>

// STD includes
#include <cassert>

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLLabelMapVolumeDisplayNode);

//----------------------------------------------------------------------------
vtkMRMLLabelMapVolumeDisplayNode::vtkMRMLLabelMapVolumeDisplayNode()
{
  this->MapToColors = vtkImageMapToColors::New();
  this->MapToColors->SetOutputFormatToRGBA();
}

//----------------------------------------------------------------------------
vtkMRMLLabelMapVolumeDisplayNode::~vtkMRMLLabelMapVolumeDisplayNode()
{
   this->MapToColors->Delete();
}

//----------------------------------------------------------------------------
void vtkMRMLLabelMapVolumeDisplayNode::SetDefaultColorMap()
{
  // set up a default color node
  // TODO: figure out if can use vtkSlicerColorLogic's helper methods
  this->SetAndObserveColorNodeID("vtkMRMLColorTableNodeLabels");
}

//----------------------------------------------------------------------------
void vtkMRMLLabelMapVolumeDisplayNode::PrintSelf(ostream& os, vtkIndent indent)
{
  
  Superclass::PrintSelf(os,indent);
}

//---------------------------------------------------------------------------
void vtkMRMLLabelMapVolumeDisplayNode::ProcessMRMLEvents ( vtkObject *caller,
                                           unsigned long event, 
                                           void *callData )
{
  Superclass::ProcessMRMLEvents(caller, event, callData);
}

//---------------------------------------------------------------------------
void vtkMRMLLabelMapVolumeDisplayNode::SetInputImageData(vtkImageData *imageData)
{
  this->MapToColors->SetInput(imageData);
}

//---------------------------------------------------------------------------
vtkImageData* vtkMRMLLabelMapVolumeDisplayNode::GetInputImageData()
{
  return vtkImageData::SafeDownCast(this->MapToColors->GetInput());
}

//---------------------------------------------------------------------------
vtkImageData* vtkMRMLLabelMapVolumeDisplayNode::GetOutputImageData()
{
  assert(!this->MapToColors->GetLookupTable() ||
         !this->MapToColors->GetLookupTable()->IsA("vtkLookupTable") ||
         vtkLookupTable::SafeDownCast(this->MapToColors->GetLookupTable())->GetNumberOfTableValues());
  return this->MapToColors->GetOutput();
}

//---------------------------------------------------------------------------
void vtkMRMLLabelMapVolumeDisplayNode::UpdateImageDataPipeline()
{
  Superclass::UpdateImageDataPipeline();

  vtkScalarsToColors *lookupTable = NULL;
  if (this->GetColorNode())
    {
    lookupTable = this->GetColorNode()->GetLookupTable();
    if (lookupTable == NULL)
      {
      if (vtkMRMLProceduralColorNode::SafeDownCast(this->GetColorNode()) != NULL)
        {
        vtkDebugMacro("UpdateImageDataPipeline: getting a color transfer function");
        lookupTable = (vtkScalarsToColors*)(vtkMRMLProceduralColorNode::SafeDownCast(this->GetColorNode())->GetColorTransferFunction());
        }
      }
    }
  if (lookupTable == NULL && this->ColorNodeID != NULL)
    {
    // only complain if there's a scene set and that scene is not batch processing
    if (this->GetScene() && !this->GetScene()->IsBatchProcessing())
      {
      vtkErrorMacro(<< "vtkMRMLLabelMapVolumeDisplayNode: Warning, the color table node: "
                    << this->ColorNodeID << " can't be found");
      }
    }
  this->MapToColors->SetLookupTable(lookupTable);
  // if there is no point, the mapping will fail (not sure)
  assert(!lookupTable || !vtkLookupTable::SafeDownCast(lookupTable) ||
         vtkLookupTable::SafeDownCast(lookupTable)->GetNumberOfTableValues());
}
