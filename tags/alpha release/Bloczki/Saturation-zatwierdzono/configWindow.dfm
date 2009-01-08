object cfgWin: TcfgWin
  Left = 401
  Top = 292
  BorderStyle = bsToolWindow
  Caption = 'Saturation'
  ClientHeight = 119
  ClientWidth = 259
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 241
    Height = 103
    Caption = 'Saturacja'
    TabOrder = 0
    object OK: TButton
      Left = 40
      Top = 67
      Width = 65
      Height = 25
      Caption = 'OK'
      TabOrder = 0
      OnClick = OKClick
    end
    object poziom: TTrackBar
      Left = 8
      Top = 16
      Width = 169
      Height = 45
      Max = 255
      Min = -255
      TabOrder = 1
      OnChange = poziomChange
    end
    object poziomShow: TEdit
      Left = 184
      Top = 18
      Width = 41
      Height = 21
      TabOrder = 2
      OnChange = poziomShowChange
    end
    object Cancel: TButton
      Left = 120
      Top = 67
      Width = 57
      Height = 25
      Caption = 'Anuluj'
      TabOrder = 3
      OnClick = CancelClick
    end
  end
end
