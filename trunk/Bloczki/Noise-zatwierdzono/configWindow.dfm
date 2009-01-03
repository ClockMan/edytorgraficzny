object cfgWin: TcfgWin
  Left = 401
  Top = 292
  BorderStyle = bsToolWindow
  Caption = 'Noise'
  ClientHeight = 135
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
    Height = 113
    Caption = 'Szum'
    TabOrder = 0
    object color: TRadioButton
      Left = 16
      Top = 88
      Width = 89
      Height = 17
      Caption = 'szum kolorowy'
      TabOrder = 0
      OnClick = colorClick
    end
    object mono: TRadioButton
      Left = 16
      Top = 64
      Width = 81
      Height = 17
      Caption = 'szum bia'#322'y'
      Checked = True
      TabOrder = 1
      TabStop = True
      OnClick = monoClick
    end
    object OK: TButton
      Left = 120
      Top = 67
      Width = 50
      Height = 25
      Caption = 'OK'
      TabOrder = 2
      OnClick = OKClick
    end
    object poziom: TTrackBar
      Left = 8
      Top = 16
      Width = 169
      Height = 45
      Max = 255
      TabOrder = 3
      OnChange = poziomChange
    end
    object poziomShow: TEdit
      Left = 184
      Top = 18
      Width = 41
      Height = 21
      TabOrder = 4
      OnChange = poziomShowChange
    end
    object Cancel: TButton
      Left = 184
      Top = 67
      Width = 50
      Height = 25
      Caption = 'Anuluj'
      TabOrder = 5
      OnClick = CancelClick
    end
  end
end
