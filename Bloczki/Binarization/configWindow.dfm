object cfgWin: TcfgWin
  Left = 392
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Binarization'
  ClientHeight = 169
  ClientWidth = 316
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 6
    Top = 8
    Width = 306
    Height = 153
    Caption = 'Binarization'
    TabOrder = 0
    object Button1: TButton
      Left = 56
      Top = 111
      Width = 75
      Height = 25
      Caption = 'OK'
      TabOrder = 0
    end
    object Button2: TButton
      Left = 185
      Top = 111
      Width = 75
      Height = 25
      Caption = 'Anuluj'
      TabOrder = 1
    end
    object CheckBox1: TCheckBox
      Left = 16
      Top = 23
      Width = 129
      Height = 17
      Caption = 'Poziom binaryzacji'
      TabOrder = 2
    end
    object limitB: TTrackBar
      Left = 16
      Top = 55
      Width = 225
      Height = 50
      Ctl3D = True
      Constraints.MaxWidth = 255
      Max = 255
      ParentCtl3D = False
      TabOrder = 3
    end
    object limitBShow: TEdit
      Left = 247
      Top = 55
      Width = 41
      Height = 21
      TabOrder = 4
    end
  end
end
