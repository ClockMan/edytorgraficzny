object cfgWindow: TcfgWindow
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Config'
  ClientHeight = 155
  ClientWidth = 369
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 353
    Height = 97
    Caption = 'Double'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Edit1: TEdit
      Left = 95
      Top = 40
      Width = 156
      Height = 21
      TabOrder = 0
      OnKeyPress = Edit1KeyPress
    end
  end
  object OK: TButton
    Left = 103
    Top = 123
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = OKClick
  end
  object Cancel: TButton
    Left = 184
    Top = 123
    Width = 75
    Height = 25
    Caption = 'Anuluj'
    TabOrder = 2
    OnClick = CancelClick
  end
end
