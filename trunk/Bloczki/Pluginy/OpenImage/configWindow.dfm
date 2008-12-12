object cfgWindow: TcfgWindow
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Config'
  ClientHeight = 200
  ClientWidth = 369
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 353
    Height = 97
    Caption = 'Bitrate obrazu'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object Open: TButton
    Left = 8
    Top = 124
    Width = 89
    Height = 25
    Caption = 'Wczytaj Obraz'
    TabOrder = 1
    OnClick = OpenClick
  end
  object EditPath: TEdit
    Left = 103
    Top = 126
    Width = 258
    Height = 21
    ReadOnly = True
    TabOrder = 2
  end
  object OK: TButton
    Left = 103
    Top = 163
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 3
    OnClick = OKClick
  end
  object Cancel: TButton
    Left = 184
    Top = 163
    Width = 75
    Height = 25
    Caption = 'Anuluj'
    TabOrder = 4
    OnClick = CancelClick
  end
  object bit_1: TRadioButton
    Left = 24
    Top = 40
    Width = 89
    Height = 17
    Caption = '1 bit na piksel'
    TabOrder = 5
  end
  object bit_4: TRadioButton
    Left = 24
    Top = 63
    Width = 89
    Height = 17
    Caption = '4 bit na piksel'
    TabOrder = 6
  end
  object bit_8: TRadioButton
    Left = 136
    Top = 40
    Width = 89
    Height = 17
    Caption = '8 bit na piksel'
    TabOrder = 7
  end
  object bit_16: TRadioButton
    Left = 136
    Top = 63
    Width = 97
    Height = 17
    Caption = '16 bit na piksel'
    TabOrder = 8
  end
  object bit_24: TRadioButton
    Left = 256
    Top = 40
    Width = 97
    Height = 17
    Caption = '24 bit na piksel'
    Checked = True
    TabOrder = 9
    TabStop = True
  end
  object bit_32: TRadioButton
    Left = 256
    Top = 63
    Width = 97
    Height = 17
    Caption = '32 bit na piksel'
    TabOrder = 10
  end
  object OpenDialog1: TOpenDialog
    Left = 96
    Top = 16
  end
end
